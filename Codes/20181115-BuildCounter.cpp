/*
 DOCUMENT NAME "20181115-BuildCounter.cpp"
 CREATION DATE 2018-11-15
 SIGNATURE CODE_20181115_BUILDCOUNTER
 COMMENT Utility that increases the number in a certain header file upon invoke
*/

#include "Overall.hpp"

// Check if this code file is enabled for testing
#ifdef CODE_20181115_BUILDCOUNTER

#include <cstdlib>
#include <iostream>
using namespace std;

const char compileTime[] = { (__DATE__ " " __TIME__) };

int main(int argc, char* argv[]) {
	cout << "Build Counter Tool, Compile Time: " << compileTime << endl;
	if (argc == 1) {
		cout << endl << "    Usage: BuildCounter <Filename>" << endl << endl;
		cout << "      This is a utility that increases the number in that given header file upon invoke." << endl;
		cout << "      File format: \"#define BUILD %d\\n\"" << endl;
		return 0;
	}

	FILE* f = fopen(argv[1], "r");
	if (!f) {
		cout << "    Error: file open failed" << endl;
		return 0;
	}

	int cnt = 0;
	fscanf(f, "#define BUILD %d", &cnt);
	fclose(f);
	f = fopen(argv[1], "w");
	fprintf(f, "#define BUILD %d\n", cnt + 1);
	fclose(f);

	cout << "Operation successful: " << cnt << " --> " << cnt + 1 << endl;

	return 0;
}

#endif

