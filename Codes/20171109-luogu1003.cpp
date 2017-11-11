/*
DOCUMENT CODE "luogu1003.cpp"
CREATION DATE 2017-11-09
SIGNATURE CODE_20171109_LUOGU1003
TOPIC
*/

#include "Overall.hpp"

//Check if this code file is enabled for testing.
#ifdef CODE_20171109_LUOGU1003

#include <cstdlib>
#include <iostream>
#include <vector>
using namespace std;

class Rect {
public:

	Rect(){}

	Rect(int left,int top,int width,int height):
		x(left),y(top),xSize(width),ySize(height)
	{}

	const bool contains(int x, int y) {
		int xEnd = this->x + xSize, yEnd = this->y + ySize;
		if (x >= this->x&&x <= xEnd&&y >= this->y&&y <= yEnd)
			return true;
		else
			return false;
	}

private:
	int x, y;
	int xSize, ySize;
};

int n;
vector<Rect> vec;
int questX, questY;

int main(int argc, char* argv[]) {
	
	cin >> n;
	vec.resize(n);

	for (Rect& i : vec) {
		int x, y, xs, ys;
		cin >> x >> y >> xs >> ys;
		i = Rect(x, y, xs, ys);
	}

	cin >> questX >> questY;
	int ans = -1;
	int id = 0;
	for (Rect& i : vec) {
		id++;
		if (i.contains(questX, questY))
			ans = id;
	}

	cout << ans << endl;

	return 0;
}

#endif
