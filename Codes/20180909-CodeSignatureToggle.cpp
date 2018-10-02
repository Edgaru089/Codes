/*
 DOCUMENT NAME "20180909-CodeSignatureToggle.cpp"
 CREATION DATE 2018-09-09
 SIGNATURE CODE_20180909_CODESIGNATURETOGGLER
 COMMENT Code Signature Toggler
*/

#include "Overall.hpp"

// Check if this code file is enabled for testing
#ifdef CODE_20180909_CODESIGNATURETOGGLER

#include <cstdlib>
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
using namespace std;

const string codeStopParsingFlag = "*/", signatureCodeFlag = "SIGNATURE", signatureHeaderFlag = "///////////////////////// Define currently tested code file /////////////////////////";

const string compileTime = string(__DATE__) + " " + string(__TIME__);

int main(int argc, char* argv[]) {

	cout << "Code Signature Toggler Tool, Compile Time: " << compileTime << endl << endl;

	if (argc < 3) {
		cout << "    Usage: CodeSignatureToggle.exe <Overall Header Filename> <Code Filename>" << endl;
		return 0;
	}

	string overallFilename(argv[1]), codeFilename(argv[2]);
	string buf, signature;
	cout << "Parsing Code File: " << codeFilename;
	ifstream fin;
	fin.open(codeFilename);
	if (!fin) {
		cout << "ERROR: Code File Input Failed." << endl;
		return EXIT_FAILURE;
	}
	while (getline(fin, buf)) {
		if (buf == codeStopParsingFlag)
			break;
		size_t pos = buf.find(signatureCodeFlag);
		if (pos != string::npos) {
			pos += signatureCodeFlag.size();
			while (isblank(buf[pos]))pos++;
			while (pos < buf.size() && !isblank(buf[pos])) {
				signature += buf[pos];
				pos++;
			}
			break;
		}
	}
	fin.close();
	if (buf.empty()) {
		cout << endl << "ERROR: No Signature Found in Source File." << endl;
		return EXIT_FAILURE;
	}
	cout << endl << "Parsing Done, Signature: " << signature << endl;

	cout << endl << "Opening Overall Header File: " << overallFilename;
	fin.open(overallFilename);
	if (!fin) {
		cout << endl << "ERROR: Overall File Input Failed." << endl;
		return EXIT_FAILURE;
	}

	vector<string> lines;
	bool found = false;
	while (getline(fin, buf)) {
		lines.push_back(buf);
		if (buf == signatureHeaderFlag) {
			cout << endl << "Overall Header Signature Located." << endl;
			char cbuf[512] = {};
			sprintf(cbuf, "#define %s", signature.c_str());
			getline(fin, buf);
			lines.push_back(string(cbuf));
			found = true;
		}
	}
	if (!found) {
		cout << endl << "ERROR: No Signature Found in Overall Header File." << endl;
		return EXIT_FAILURE;
	}
	cout << endl << "Writing Overall Header File...";
	fin.close();
	ofstream fout(overallFilename);
	if (!fout) {
		cout << endl << "ERROR: Overall Header Output Failed." << endl;
	}
	for (auto& s : lines)
		fout << s << '\n';
	fout.close();
	cout << endl << "File Written." << endl;

	return 0;
}

#endif

