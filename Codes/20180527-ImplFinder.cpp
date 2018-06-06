/*
DOCUMENT CODE "20180527-ImplFinder.cpp"
CREATION DATE 2018-05-27
SIGNATURE CODE_20180527_IMPLFINDER
TOPIC
*/

#include "Overall.hpp"

//Check if this code file is enabled for testing.
#ifdef CODE_20180527_IMPLFINDER

#include <cstdlib>
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <cstring>

#include <Windows.h>

using namespace std;


const string compileTime = string(__DATE__) + " " + string(__TIME__);

string filter, outputName;
vector<string> filenames;


int main(int argc, char* argv[]) {

	cout << "Code File Batch Include Tool, Compile Time: " << compileTime << endl << endl;
	if (argc < 3) {
		cout << "    Usage: CodeBatch <Filter> <OutputFile>" << endl << endl;
		cout << "      This tool will generate a header code that will include all files" << endl <<
			"    found by the filter and output the contents into a file." << endl << endl;
		return 0;
	}

	filter = string(argv[1]);
	outputName = string(argv[2]);

	cout << "    Filter: " << filter << (argc > 2 ? ", Output File: " : ", Output File: [Default]") << outputName << endl;

	WIN32_FIND_DATA fileData;

	HANDLE fileHandle = FindFirstFile((R"(.\)" + filter).c_str(), &fileData);

	if (fileHandle == (void*)ERROR_INVALID_HANDLE ||
		fileHandle == (void*)ERROR_FILE_NOT_FOUND ||
		strcmp(fileData.cFileName, "") == 0) {
		cout << endl << "    Warning: No Found Found" << endl <<
			"    File not changed.";
		return 0;
	}

	// Loop over every plugin in the folder, and store
	// the handle in our modules list
	do {

		filenames.push_back(string(fileData.cFileName));

		// Continue while there are more files to find
	} while (FindNextFile(fileHandle, &fileData));

	FindClose(fileHandle);

	cout << endl << "    Found Files: ( " << filenames.size() << " )";
	for (string& i : filenames)
		cout << endl << "        * " << i;

	// Write to the ImplList.hpp file
	// Open a file stream
	ofstream fout;
	fout.open(outputName, ios_base::out);
	if (!fout.good()) {
		cout << "    Error: File output stream failed upon initalaization" << endl;
		return 1;
	}

	fout << "#pragma once\n\n";
	for (string& i : filenames)
		fout << "#include \"" << i << "\"\n";
	fout << '\n' << flush;
	fout.close();

	cout << endl << endl << "    Operation successful." << endl;

	return 0;
}

#endif

