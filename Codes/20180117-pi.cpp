/*
DOCUMENT CODE "20180117-pi.cpp"
CREATION DATE 2018-01-17
SIGNATURE CODE_20180117_PI
TOPIC
*/

#include "Overall.hpp"

//Check if this code file is enabled for testing.
#ifdef CODE_20180117_PI

#include <cstdlib>
#include <iostream>
#include <iomanip>

#include <vector>
#include <queue>
#include <memory>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <future>
#include <functional>
#include <stdexcept>

#include <SFML/System.hpp>

using namespace std;
using namespace sf;

class ThreadPool {
public:
	ThreadPool(size_t);
	template<class F, class... Args>
	auto enqueue(F&& f, Args&&... args)
		->std::future<typename std::result_of<F(Args...)>::type>;
	~ThreadPool();
private:
	// need to keep track of threads so we can join them
	std::vector< std::thread > workers;
	// the task queue
	std::queue< std::function<void()> > tasks;

	// synchronization
	std::mutex queue_mutex;
	std::condition_variable condition;
	bool stop;
};

// the constructor just launches some amount of workers
inline ThreadPool::ThreadPool(size_t threads)
	: stop(false) {
	for (size_t i = 0; i < threads; ++i)
		workers.emplace_back(
			[this] {
		for (;;) {
			std::function<void()> task;

			{
				std::unique_lock<std::mutex> lock(this->queue_mutex);
				this->condition.wait(lock,
					[this] { return this->stop || !this->tasks.empty(); });
				if (this->stop && this->tasks.empty())
					return;
				task = std::move(this->tasks.front());
				this->tasks.pop();
			}

			task();
		}
	}
	);
}

// add new work item to the pool
template<class F, class... Args>
auto ThreadPool::enqueue(F&& f, Args&&... args)
-> std::future<typename std::result_of<F(Args...)>::type> {
	using return_type = typename std::result_of<F(Args...)>::type;

	auto task = std::make_shared< std::packaged_task<return_type()> >(
		std::bind(std::forward<F>(f), std::forward<Args>(args)...)
		);

	std::future<return_type> res = task->get_future();
	{
		std::unique_lock<std::mutex> lock(queue_mutex);

		// don't allow enqueueing after stopping the pool
		if (stop)
			throw std::runtime_error("enqueue on stopped ThreadPool");

		tasks.emplace([task]() { (*task)(); });
	}
	condition.notify_one();
	return res;
}

// the destructor joins all threads
inline ThreadPool::~ThreadPool() {
	{
		std::unique_lock<std::mutex> lock(queue_mutex);
		stop = true;
	}
	condition.notify_all();
	for (std::thread &worker : workers)
		worker.join();
}




int main(int argc, char* argv[]) {
	cout << "Steps: ";

	long long n;
	cin >> n;
	double pi = 0;
	double sum;
	Clock cl;
	cl.restart();
	for (long long i = 1; i <= n; i++) {
		sum = 4.0 / (2.0 * i - 1.0);
		if (((i + 1) & 1))
			sum *= -1.0;
		pi += sum;
		if (cl.getElapsedTime() >= milliseconds(100)) {
			cl.restart();
			printf("\r%.20lf", pi);
		}
	}
	return 0;
}

#endif

