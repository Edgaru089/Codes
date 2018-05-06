/*
DOCUMENT CODE "20180430-luogu1449.cpp"
CREATION DATE 2018-04-30
SIGNATURE CODE_20180430_LUOGU1449
TOPIC
*/

#include "Overall.hpp"

//Check if this code file is enabled for testing.
#ifdef CODE_20180430_LUOGU1449

#include <cstdlib>
#include <iostream>
#include <stack>
#include <string>
#include <cctype>
using namespace std;

static const string toString(bool                   data) { char buff[48]; sprintf(buff, "%d", data);   return string(buff); }
static const string toString(short                  data) { char buff[48]; sprintf(buff, "%d", data);   return string(buff); }
static const string toString(unsigned short         data) { char buff[48]; sprintf(buff, "%d", data);   return string(buff); }
static const string toString(int                    data) { char buff[48]; sprintf(buff, "%d", data);   return string(buff); }
static const string toString(unsigned int           data) { char buff[48]; sprintf(buff, "%u", data);   return string(buff); }
static const string toString(long long              data) { char buff[48]; sprintf(buff, "%lld", data); return string(buff); }
static const string toString(unsigned long long     data) { char buff[48]; sprintf(buff, "%llu", data); return string(buff); }
static const string toString(float                  data) { char buff[48]; sprintf(buff, "%f", data);   return string(buff); }
static const string toString(double                 data) { char buff[48]; sprintf(buff, "%lf", data);  return string(buff); }

static const bool      toBool(string&     data) { int x;       sscanf(data.c_str(), "%d", &x);   return x; }
static const short     toShort(string&    data) { int x;       sscanf(data.c_str(), "%d", &x);   return x; }
static const int       toInt(string&      data) { int x;       sscanf(data.c_str(), "%d", &x);   return x; }
static const long long toLongLong(string& data) { long long x; sscanf(data.c_str(), "%lld", &x); return x; }
static const float     toFloat(string&    data) { float x;     sscanf(data.c_str(), "%f", &x);   return x; }
static const double    toDouble(string&   data) { double x;    sscanf(data.c_str(), "%lf", &x);  return x; }

string str;
stack<int> st;

int calculate(char op, int x, int y) {
	if (op == '+')
		return x + y;
	else if (op == '-')
		return x - y;
	else if (op == '*')
		return x * y;
	else if (op == '/')
		return x / y;
	else
		return 0;
}

int main(int argc, char* argv[]) {
	
	getline(cin, str);

	int i = 0;
	while (i < str.length()) {

		while (str[i] != '+'&&str[i] != '-'&&str[i] != '*'&&str[i] != '/' && !isdigit(str[i]))
			i++;

		while (str[i] == '+' || str[i] == '-' || str[i] == '*' || str[i] == '/') {
			int x = st.top(); st.pop();
			int y = st.top(); st.pop();
			st.push(calculate(str[i], y, x));
			i++;
		}

		string tmp;
		while (isdigit(str[i])) {
			tmp += str[i];
			i++;
		}

		if (str[i] == '@')
			break;

		st.push(toInt(tmp));
		
	}

	cout << st.top() << endl;

	return 0;
}

#endif

