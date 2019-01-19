/*
 DOCUMENT NAME "20190119-luogu1054.cpp"
 CREATION DATE 2019-01-19
 SIGNATURE CODE_20190119_LUOGU1054
 COMMENT P1054 等价表达式（bndsoj0656）
*/

#include "Overall.hpp"

// Check if this code file is enabled for testing
#ifdef CODE_20190119_LUOGU1054

#include <cstdlib>
#include <iostream>
#include <cstdio>
#include <cctype>
#include <memory>
#include <vector>
#include <list>
#include <string>
#include <valarray>
using namespace std;

#if (defined LOCAL) || (defined D)
#define DEBUG(...) printf(__VA_ARGS__)
#define PRINTARR(formatstr, arr, beginoff, size)				\
do{printf(#arr ":");											\
for (int __i = beginoff; __i <= beginoff + size - 1; __i++)		\
	printf("\t%d", __i);										\
printf("\n");													\
for (int __i = beginoff; __i <= beginoff + size - 1; __i++)		\
	printf("\t" formatstr, arr[__i]);							\
printf("\n"); }while(false)
#define PASS printf("Passing function \"%s\" on line %d\n", __func__, __LINE__)
#define ASSERT(expr) do{\
	if(!(expr)){\
		printf("Debug Assertation Failed on line %d, in function %s:\n  Expression: %s\n",__LINE__,__func__,#expr);\
		abort();\
	}\
}while(false)
#else
#define DEBUG(...)
#define PRINTARR(a, b, c, d)
#define PASS
#define ASSERT(expr)
#endif

typedef long long ll;
const int Mod = 4e5 + 7;

template<typename IntType>
class Node : public enable_shared_from_this<Node<IntType>> {
public:

	class ParamInvalidException : public exception {
	public:
		const char* what() const noexcept override {
			return "Node Paramater Invalid";
		}
	};

	typedef IntType Int;
	typedef shared_ptr<Node> Ptr;

	virtual ~Node() {}

	virtual bool wantCheckParams() { return true; }

	virtual Int get() {
		if (wantCheckParams() && (!leftParam || !rightParam))
			throw ParamInvalidException();
		return _get();
	}
	Int operator () () { return get(); }

	void setParamaters(Node::Ptr leftParam, Node::Ptr rightParam) {
		if (leftParam)
			this->leftParam = leftParam;
		if (rightParam)
			this->rightParam = rightParam;
	}

	pair<Node::Ptr, Node::Ptr> getParamaters() {
		return make_pair(leftParam, rightParam);
	}

//protected:
	Node::Ptr leftParam, rightParam;

private:
	virtual Int _get() = 0;
};

typedef Node<ll> NodeLL;

class AddNode :public NodeLL {
	Int _get() override { return (leftParam->get() + rightParam->get()) % Mod; }
};
class SubtractNode :public NodeLL {
	Int _get() override { return (leftParam->get() - rightParam->get() + Mod) % Mod; }
};
class MultiplyNode :public NodeLL {
	Int _get() override { return (leftParam->get() * rightParam->get()) % Mod; }
};
class PowerNode :public NodeLL {
	Int _get() override {
		Int base = leftParam->get(), exp = rightParam->get();
		Int ans = 1;
		while (exp) {
			if (exp & 1)
				ans = (ans*base) % Mod;
			base = (base*base) % Mod;
			exp >>= 1;
		}
		return ans;
	}
};
class ConstNode :public NodeLL {
public:
	ConstNode() {}
	ConstNode(Int val) { this->val = val % Mod; }
	void setVal(Int val) { this->val = val % Mod; }
	bool wantCheckParams() override { return false; }
private:
	Int _get() override { return val; }
	Int val;
};

class Tokenizer {
public:
	enum Type {
		Unknown,
		Identifier,
		Number,
		Symbol
	};

	struct Token {
		Type type;
		string word;
	};

	template<typename Container>
	static void tokenize(const string& str, Container& tokens) {
		tokens.clear();
		Token buffer{ Unknown, "" };
		for (char c : str) {
			if (!(isblank(c) || iscntrl(c) || c == ',')) {
				if ((buffer.type == Number && !isdigit(c)) ||
					(buffer.type == Identifier && (!isalnum(c) && c != '_')) ||
					(buffer.type == Symbol)) {
					tokens.push_back(buffer);
					buffer = Token{ Unknown, "" };
				}
				if (buffer.type == Unknown) {
					// Check new object type
					if (isalpha(c) || c == '_')
						buffer.type = Identifier;
					else if (isdigit(c))
						buffer.type = Number;
					else
						buffer.type = Symbol;
				}
				buffer.word.push_back(c);
			} else {
				if (buffer.type != Unknown) {
					tokens.push_back(buffer);
					buffer = Token{ Unknown, "" };
				}
			}
		}
		if (buffer.type != Unknown) {
			tokens.push_back(buffer);
			buffer = Token{ Unknown, "" };
		}
	}
};

class NodeTree {
public:

	void parse(string str) {
		while (iscntrl(str.back()) || str.back() == ' ' || str.back() == '\t')
			str.pop_back();

		vector<Tokenizer::Token> vec;
		Tokenizer::tokenize(str, vec);

		variable = make_shared<ConstNode>();
		valarray<Tokenizer::Token> arr(vec.data(), vec.size());
		root = _parse(arr);
	}

	int getValue(int var) {
		variable->setVal(var);
		return root->get();
	}

	void clear() {
		root = nullptr;
		variable = nullptr;
	}

private:

	NodeLL::Ptr _parse(valarray<Tokenizer::Token> str) {
		list<pair<NodeLL::Ptr, string>> nodes;
		typedef list<pair<NodeLL::Ptr, string>>::iterator iter;

		// Populate
		for (auto i : str) {
			switch (i.type) {
				case Tokenizer::Identifier: {
					ASSERT(i.word == "a");
					nodes.push_back(make_pair(variable, i.word));
					break;
				}
				case Tokenizer::Number:
					nodes.push_back(make_pair(make_shared<ConstNode>(atoi(i.word.c_str())), i.word));
					break;
				case Tokenizer::Symbol:
					switch (i.word[0]) {
						case '+':
							nodes.push_back(make_pair(make_shared<AddNode>(), i.word));
							break;
						case '-':
							nodes.push_back(make_pair(make_shared<SubtractNode>(), i.word));
							break;
						case '*':
							nodes.push_back(make_pair(make_shared<MultiplyNode>(), i.word));
							break;
						case '^':
							nodes.push_back(make_pair(make_shared<PowerNode>(), i.word));
							break;
						case '(':
						case ')':
							nodes.push_back(make_pair(nullptr, i.word));
							break;
					}
					break;
			}
		}

		// Bracelets
		int k = 0;
		for (iter i = nodes.begin(); i != nodes.end(); i++, k++) {
			const auto p = i->first; const auto t = i->second;
			if (t == "(") {
				int offset = k + 1;
				int layers = 1;
				i = nodes.erase(i);
				while (layers > 0 && i != nodes.end()) {
					if (i->second == "(")
						layers++;
					if (i->second == ")")
						layers--;
					i = nodes.erase(i);
					k++;
				}
				int len = k - offset;
				if (layers > 0)
					len++;
				i = nodes.insert(i, make_pair(_parse(str[slice(offset, len, 1)]), "$("));
			}
		}

		// Power
		k = 0;
		for (iter i = nodes.begin(); i != nodes.end(); i++, k++) {
			const auto p = i->first; const auto t = i->second;
			if (t == "^") {
				iter cur = i;
				i--; iter l = i;
				i++; i++; iter r = i;
				i++;
				auto obj = make_shared<PowerNode>();
				obj->setParamaters(l->first, r->first);
				nodes.erase(l);
				nodes.erase(cur);
				nodes.erase(r);
				i = nodes.insert(i, make_pair(obj, "$^"));
			}
		}

		// Multiply
		k = 0;
		for (iter i = nodes.begin(); i != nodes.end(); i++, k++) {
			const auto p = i->first; const auto t = i->second;
			if (t == "*") {
				iter cur = i;
				i--; iter l = i;
				i++; i++; iter r = i;
				i++;
				auto obj = make_shared<MultiplyNode>();
				obj->setParamaters(l->first, r->first);
				nodes.erase(l);
				nodes.erase(cur);
				nodes.erase(r);
				i = nodes.insert(i, make_pair(obj, "$*"));
			}
		}

		// Add and Subtract
		k = 0;
		for (iter i = nodes.begin(); i != nodes.end(); i++, k++) {
			const auto p = i->first; const auto t = i->second;
			if (t == "+" || t == "-") {
				iter cur = i;
				i--; iter l = i;
				i++; i++; iter r = i;
				i++;
				NodeLL::Ptr obj;
				if (t == "+")
					obj = make_shared<AddNode>();
				else
					obj = make_shared<SubtractNode>();
				obj->setParamaters(l->first, r->first);
				nodes.erase(l);
				nodes.erase(cur);
				nodes.erase(r);
				i = nodes.insert(i, make_pair(obj, "$*"));
			}
		}

		ASSERT(nodes.size() == 1);
		return nodes.front().first;
	}

	NodeLL::Ptr root;
	shared_ptr<ConstNode> variable;
};

int n;
NodeTree st, x;
string buf;

int main(int argc, char* argv[]) {

	srand(838949721); // randomly typed; not purely random of course

	getline(cin, buf);
	st.parse(buf);

	cin >> n;
	for (int i = 0; i < n; i++) {
		while (getline(cin, buf) && (buf.empty() || buf == "\r"));
		x.clear();
		x.parse(buf);
		bool flag = true;
		for (int i = 1; i <= 20 && flag; i++) {
			int v = rand();
			if (st.getValue(v) != x.getValue(v))
				flag = false;
		}
		if (flag)
			cout << (char)('A' + i);
	}

	cout << endl;

	return 0;
}

#endif

