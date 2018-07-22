/*
DOCUMENT CODE "CodeSubmit.cpp"
CREATION DATE 2017-11-09
SIGNATURE CODE_20171109_CODESUBMIT
TOPIC
*/

#include "Overall.hpp"

//Check if this code file is enabled for testing.
#ifdef CODE_20171109_CODESUBMIT

#include <cstdlib>
#include <iostream>
#include <fstream>
#include <vector>

#include <SFML/Window/Clipboard.hpp>

#include <Windows.h>

using namespace std;

const string compileTime = string(__DATE__) + " " + string(__TIME__);

vector<string> lines;
vector<bool> excluded;

const string replaceAll(string source, string from, string to) {
	string str = "";
	for (int i = 0; i < source.size() - from.size(); i++) {
		if (source.substr(i, from.size()) == from) {
			i += from.size() - 1;
			str += to;
		}
		else
			str += source[i];
	}
	return str;
}

const int excludeFirst(const string content) {
	for (int i = 0; i < lines.size(); i++) {
		if (lines[i].substr(0, content.size()) == content) {
			excluded[i] = true;
			return i;
		}
		if (i == lines.size() - 1)  // No such string was found
			cout << "    Warning: No \"" << content << "\" was found." << endl;
	}
	return -1;
}

const int excludeLast(const string content) {
	int lastPos = -1;
	for (int i = 0; i < lines.size(); i++) {
		if (lines[i].substr(0, content.size()) == content)
			lastPos = i;
	}
	if (lastPos == -1)  // No such string was found
		cout << "    Warning: No \"" << content << "\" was found." << endl;
	else
		excluded[lastPos] = true;
	return lastPos;
}

string mergeString() {
	string ans = "";
	for (int i = 0; i < lines.size(); i++)
		if (!excluded[i]) {
			ans += lines[i];
			ans += "\r\n";
		}
	return ans;
}

sf::String convert(string str) {
	wchar_t wstr[32 * 1024];
	wstr[MultiByteToWideChar(936, 0, str.c_str(), str.size(), wstr, 32 * 1024)] = '\0';
	return sf::String(wstr);
}

int main(int argc, char* argv[]) {
	cout << "Code Submitter Tool, Compile Time: " << compileTime << endl << endl;
	if (argc == 1) {
		cout << "    Usage: CodeSubmit <Filename> [OutputFile]" << endl << endl;
		cout << "      This tool will generate a submittable file base on the code, copy it" << endl <<
			"    to the clipboard and output the result into a new file if nesscerry." << endl << endl;
		return 0;
	}

	// Open a file input stream
	ifstream fin;
	fin.open(argv[1], ios_base::in);
	if (!fin.good()) {
		cout << "    Error: Filestream failed upon initalaization" << endl;
		return 1;
	}

	// Input code line by line
	string str;
	while (!getline(fin, str).eof())
		lines.push_back(str);
	excluded.resize(lines.size(), false);

	// Close the file
	fin.close();

	int pos = -1;
	// Delete the first #include, the first // comment, the first #ifdef and the newlines before them
	excluded[excludeFirst("#include") - 1] = true;
	excluded[excludeFirst("//") - 1] = true;
	excludeFirst("#ifdef");

	//Delete the last #endif and the newline before it
	excluded[excludeLast("#endif") - 1] = true;

	// Merge the result
	string result = mergeString();

	// Output
	cout << "    Operation complete: \n +-------------------- Code --------------------+" << endl;
	cout << replaceAll(result, "\r\n", "\n") << endl << " +------------------ End Code ------------------+" << endl;

	// Copy to clipboard
	sf::Clipboard::setString(convert(result));
	cout << "    Copied to clipboard." << endl;

	// Output to a new file if nesscerry
	if (argc >= 3) {
		if ((ofstream(argv[2]) << replaceAll(result, "\r\n", "\n") << flush).good())
			cout << "    Outputed to file: \"" << argv[2] << "\"" << endl;
		else
			cout << "File output failed: \"" << argv[2] << "\"" << endl;
	}

	return 0;
}

#endif
