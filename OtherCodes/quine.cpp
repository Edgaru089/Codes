#include <cstdlib>
#include <iostream>
#include <vector>
#include <string>
using namespace std;
vector<string> v={
"#include <cstdlib>",
"#include <iostream>",
"#include <vector>",
"#include <string>",
"using namespace std;",
"vector<string> v={",
"};",
"int main(int argc, char* argv[]) {",
"	for(int i=0;i<6;i++)",
"		cout<<v[i]<<endl;",
"	for(const string& s:v)",
"		cout<<(char)34<<s<<(char)34<<','<<endl;",
"	for(int i=6;i<v.size();i++)",
"		cout<<v[i]<<endl;",
"	return 0;",
"}",
};
int main(int argc, char* argv[]) {
	for(int i=0;i<6;i++)
		cout<<v[i]<<endl;
	for(const string& s:v)
		cout<<(char)34<<s<<(char)34<<','<<endl;
	for(int i=6;i<v.size();i++)
		cout<<v[i]<<endl;
	return 0;
}
