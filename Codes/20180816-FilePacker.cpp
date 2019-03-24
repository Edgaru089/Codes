/*
DOCUMENT NAME "20180816-FilePacker.cpp"
CREATION DATE 2018-08-16
SIGNATURE CODE_20180816_FILEPACKER
COMMENT A utility for packing assets into one file
*/

#include "Overall.hpp"

// Check if this code file is enabled for testing
#ifdef CODE_20180816_FILEPACKER

#include <cstdlib>
#include <iostream>
#include <string>
#include <cstring>
#include <unordered_map>
#include <functional>
#include <fstream>
#include <sstream>
#include <SFML/Graphics.hpp>
using namespace std;
using namespace sf;


class StringParser {
public:
	static const string toString(bool                   data) { return to_string((int)data); }
	static const string toString(short                  data) { return to_string((int)data); }
	static const string toString(unsigned short         data) { return to_string((int)data); }
	static const string toString(int                    data) { return to_string(data); }
	static const string toString(unsigned int           data) { return to_string(data); }
	static const string toString(long long              data) { return to_string(data); }
	static const string toString(unsigned long long     data) { return to_string(data); }
	static const string toString(float                  data) { return to_string(data); }
	static const string toString(double                 data) { return to_string(data); }

	static const bool      toBool(string&     data) { int x;       sscanf(data.c_str(), "%d", &x);   return x; }
	static const short     toShort(string&    data) { int x;       sscanf(data.c_str(), "%d", &x);   return x; }
	static const int       toInt(string&      data) { int x;       sscanf(data.c_str(), "%d", &x);   return x; }
	static const long long toLongLong(string& data) { long long x; sscanf(data.c_str(), "%lld", &x); return x; }
	static const float     toFloat(string&    data) { float x;     sscanf(data.c_str(), "%f", &x);   return x; }
	static const double    toDouble(string&   data) { double x;    sscanf(data.c_str(), "%lf", &x);  return x; }

	template<typename... Args>
	static const string format(const string& formatStr, const Args&... args) {
		char buffer[256];
		sprintf(buffer, formatStr.c_str(), args...);
		return string(buffer);
	}
};

class AssetManager {
public:

	struct Asset {
		Asset() :textureRect(0, 0, 0, 0) {}
		Asset(string id, string filename, string type) :
			strid(id), filename(filename), type(type), textureRect(0, 0, 0, 0) {}
		Asset(string id, string filename, string type, IntRect textureRect) :
			strid(id), filename(filename), type(type), textureRect(textureRect) {}

		string strid, filename, type;
		IntRect textureRect;
	};

	bool loadListFile(string filename = "assets.list");

	string getAssetFilename(string id);

	unordered_map<string, Asset>& getAssetMapper() { return assets; }

private:

	unordered_map<string, Asset> assets;

};

AssetManager assetManager;

struct FileData {
	Uint64 offset, length;
};

unordered_map<string, FileData> fileLocations;
vector<char> outdata;
char buf[32 * 1024 * 1024];

const string compileTime = string(__DATE__) + " " + string(__TIME__);

int main(int argc, char* argv[]) {
	cout << "File Package Tool, Compile Time: " << compileTime << endl << endl;
	if (argc < 3) {
		cout << "    Usage: FilePack <Asset List> <Output File>" << endl << endl;
		cout << "      This tool will generate a package file that will include all files" << endl <<
			"    include all the file found int the list." << endl << endl;
		return 0;
	}

	string assetFile = argv[1], outputFile = argv[2];
	if (!assetManager.loadListFile(assetFile)) {
		cout << "Asset File unloaded." << endl;
		return 1;
	}

	cout << "Loading Files..." << flush;
	for (auto& i : assetManager.getAssetMapper()) {
		string& filename = i.second.filename;
		if (fileLocations.find(filename) == fileLocations.end()) {
			FileData data = FileData{ outdata.size(), 0 };
			ifstream fin(filename, ifstream::binary);
			cout << endl << "    " << filename;
			if (!fin) {
				cout << "[ERROR] File \"" << filename << "\" failed to open." << endl;
				return 1;
			}
			while (!fin.eof()) {
				fin.read(buf, sizeof(buf));
				outdata.reserve(outdata.size() + fin.gcount());
				for (int i = 0; i < fin.gcount(); i++)
					outdata.push_back(buf[i]);
			}
			data.length = outdata.size() - data.offset;
			fileLocations.insert(make_pair(filename, data));
		}
	}
	cout << endl << "Files Loaded." << endl;
	cout << "Done." << endl;

	ostringstream ostr;
	for (auto& i : assetManager.getAssetMapper()) {
		string line = StringParser::format("$ %s %s {OFF%llu, LEN%llu}",
			i.second.type.c_str(), i.second.strid.c_str(), fileLocations[i.second.filename].offset, fileLocations[i.second.filename].length);
		if (i.second.textureRect != IntRect(0, 0, 0, 0))
			line += StringParser::format(" [%d, %d, %dx%d]", i.second.textureRect.left, i.second.textureRect.top, i.second.textureRect.width, i.second.textureRect.height);
		//cout << line << endl;
		ostr << line << '\n';
	}
	ostr.flush();
	string liststr = ostr.str();

	ofstream fout(outputFile, ofstream::binary);
	// hello!
	fout.write("Edgaru089 Package! 0=w=0", 24);
	// output list size (8-byte) in little-endian
	Uint64 listlen = liststr.size();
	for (int i = 0; i < 8; i++) {
		fout.put((char)(listlen & 0xff));
		listlen >>= 8;
	}
	// output list file
	fout.write(liststr.c_str(), liststr.size());
	// output data
	fout.write(outdata.data(), outdata.size());
	fout.flush();
	cout << "File packing complete, written " << fileLocations.size() << " files, " << fout.tellp() << " bytes." << endl;
	fout.close();

	return 0;
}


////////////////////////////////////////
bool AssetManager::loadListFile(string filename) {
	cout << "Loading asset list...";
	ifstream fin(filename);
	if (fin.bad()) {
		cout << " [ERROR] File failed to open." << endl;
		return false;
	}
	string str;
	string assetType;
	while (getline(fin, str)) {
		char type = str[0];
		if (type == '#') // Comment line
			continue;
		else if (type == '[') { // Set asset type
			size_t end = str.find_first_of(']');
			assetType = str.substr(1, end - 1);
		}
		else if (type == '$') { // Asset line
			string id, file;
			IntRect rect(0, 0, 0, 0);
			size_t i = 1;
			// Find first non-blank character
			while (str[i] == ' ' || str[i] == '\t')
				i++;
			// Read the asset id
			while (!isspace(str[i])) {
				id += str[i];
				i++;
			}
			// Find first non-blank character
			while (str[i] == ' ' || str[i] == '\t')
				i++;
			// Read the filename
			while (i < str.size() && str[i] != '[' && !isspace(str[i])) {
				file += str[i];
				i++;
			}
			// Find texure rect info if possible
			while (i < str.size() && str[i] != '[')
				i++;
			// Has texture rect infomation - read it
			if (i < str.size() && str[i] == '[') {
				string left, top, width, height;
				// Every value is not negative
				// Read left
				while (!isdigit(str[i]))
					i++;
				while (isdigit(str[i])) {
					left += str[i];
					i++;
				}
				//Read top
				while (!isdigit(str[i]))
					i++;
				while (isdigit(str[i])) {
					top += str[i];
					i++;
				}
				//Read width
				while (!isdigit(str[i]))
					i++;
				while (isdigit(str[i])) {
					width += str[i];
					i++;
				}
				//Read height
				while (!isdigit(str[i]))
					i++;
				while (isdigit(str[i])) {
					height += str[i];
					i++;
				}
				rect = IntRect(StringParser::toInt(left), StringParser::toInt(top),
							   StringParser::toInt(width), StringParser::toInt(height));
			}
			assets.insert(make_pair(id, Asset(id, file, assetType, rect)));
		}
	}
	cout << " Asset file loaded." << endl;
	return true;
}


////////////////////////////////////////
string AssetManager::getAssetFilename(string id) {
	auto p = assets.find(id);
	if (p != assets.end())
		return p->second.filename;
	else
		return "";
}

#endif

