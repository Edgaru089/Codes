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

class SHA256
{
protected:
	typedef unsigned char uint8;
	typedef unsigned int uint32;
	typedef unsigned long long uint64;

	const static uint32 sha256_k[];
	static const unsigned int SHA224_256_BLOCK_SIZE = (512 / 8);
public:
	void init();
	void update(const unsigned char *message, unsigned int len);
	void final(unsigned char *digest);
	static const unsigned int DIGEST_SIZE = (256 / 8);

protected:
	void transform(const unsigned char *message, unsigned int block_nb);
	unsigned int m_tot_len;
	unsigned int m_len;
	unsigned char m_block[2 * SHA224_256_BLOCK_SIZE];
	uint32 m_h[8];
};

std::string sha256(std::string input);
string sha256(vector<char>& input);

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
	cout << "Calculating SHA-256 Digest...";
	string digest = sha256(outdata);
	cout << "Done." << endl;

	ostringstream ostr;
	ostr << StringParser::format("%%sha256 %s\n", digest.c_str());
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
#define SHA2_SHFR(x, n)    (x >> n)
#define SHA2_ROTR(x, n)   ((x >> n) | (x << ((sizeof(x) << 3) - n)))
#define SHA2_ROTL(x, n)   ((x << n) | (x >> ((sizeof(x) << 3) - n)))
#define SHA2_CH(x, y, z)  ((x & y) ^ (~x & z))
#define SHA2_MAJ(x, y, z) ((x & y) ^ (x & z) ^ (y & z))
#define SHA256_F1(x) (SHA2_ROTR(x,  2) ^ SHA2_ROTR(x, 13) ^ SHA2_ROTR(x, 22))
#define SHA256_F2(x) (SHA2_ROTR(x,  6) ^ SHA2_ROTR(x, 11) ^ SHA2_ROTR(x, 25))
#define SHA256_F3(x) (SHA2_ROTR(x,  7) ^ SHA2_ROTR(x, 18) ^ SHA2_SHFR(x,  3))
#define SHA256_F4(x) (SHA2_ROTR(x, 17) ^ SHA2_ROTR(x, 19) ^ SHA2_SHFR(x, 10))
#define SHA2_UNPACK32(x, str)                 \
{                                             \
    *((str) + 3) = (uint8) ((x)      );       \
    *((str) + 2) = (uint8) ((x) >>  8);       \
    *((str) + 1) = (uint8) ((x) >> 16);       \
    *((str) + 0) = (uint8) ((x) >> 24);       \
}
#define SHA2_PACK32(str, x)                   \
{                                             \
    *(x) =   ((uint32) *((str) + 3)      )    \
           | ((uint32) *((str) + 2) <<  8)    \
           | ((uint32) *((str) + 1) << 16)    \
           | ((uint32) *((str) + 0) << 24);   \
} 

const unsigned int SHA256::sha256_k[64] = //UL = uint32
{ 0x428a2f98, 0x71374491, 0xb5c0fbcf, 0xe9b5dba5,
0x3956c25b, 0x59f111f1, 0x923f82a4, 0xab1c5ed5,
0xd807aa98, 0x12835b01, 0x243185be, 0x550c7dc3,
0x72be5d74, 0x80deb1fe, 0x9bdc06a7, 0xc19bf174,
0xe49b69c1, 0xefbe4786, 0x0fc19dc6, 0x240ca1cc,
0x2de92c6f, 0x4a7484aa, 0x5cb0a9dc, 0x76f988da,
0x983e5152, 0xa831c66d, 0xb00327c8, 0xbf597fc7,
0xc6e00bf3, 0xd5a79147, 0x06ca6351, 0x14292967,
0x27b70a85, 0x2e1b2138, 0x4d2c6dfc, 0x53380d13,
0x650a7354, 0x766a0abb, 0x81c2c92e, 0x92722c85,
0xa2bfe8a1, 0xa81a664b, 0xc24b8b70, 0xc76c51a3,
0xd192e819, 0xd6990624, 0xf40e3585, 0x106aa070,
0x19a4c116, 0x1e376c08, 0x2748774c, 0x34b0bcb5,
0x391c0cb3, 0x4ed8aa4a, 0x5b9cca4f, 0x682e6ff3,
0x748f82ee, 0x78a5636f, 0x84c87814, 0x8cc70208,
0x90befffa, 0xa4506ceb, 0xbef9a3f7, 0xc67178f2 };

void SHA256::transform(const unsigned char *message, unsigned int block_nb)
{
	uint32 w[64];
	uint32 wv[8];
	uint32 t1, t2;
	const unsigned char *sub_block;
	int i;
	int j;
	for (i = 0; i < (int)block_nb; i++) {
		sub_block = message + (i << 6);
		for (j = 0; j < 16; j++) {
			SHA2_PACK32(&sub_block[j << 2], &w[j]);
		}
		for (j = 16; j < 64; j++) {
			w[j] = SHA256_F4(w[j - 2]) + w[j - 7] + SHA256_F3(w[j - 15]) + w[j - 16];
		}
		for (j = 0; j < 8; j++) {
			wv[j] = m_h[j];
		}
		for (j = 0; j < 64; j++) {
			t1 = wv[7] + SHA256_F2(wv[4]) + SHA2_CH(wv[4], wv[5], wv[6])
				+ sha256_k[j] + w[j];
			t2 = SHA256_F1(wv[0]) + SHA2_MAJ(wv[0], wv[1], wv[2]);
			wv[7] = wv[6];
			wv[6] = wv[5];
			wv[5] = wv[4];
			wv[4] = wv[3] + t1;
			wv[3] = wv[2];
			wv[2] = wv[1];
			wv[1] = wv[0];
			wv[0] = t1 + t2;
		}
		for (j = 0; j < 8; j++) {
			m_h[j] += wv[j];
		}
	}
}

void SHA256::init()
{
	m_h[0] = 0x6a09e667;
	m_h[1] = 0xbb67ae85;
	m_h[2] = 0x3c6ef372;
	m_h[3] = 0xa54ff53a;
	m_h[4] = 0x510e527f;
	m_h[5] = 0x9b05688c;
	m_h[6] = 0x1f83d9ab;
	m_h[7] = 0x5be0cd19;
	m_len = 0;
	m_tot_len = 0;
}

void SHA256::update(const unsigned char *message, unsigned int len)
{
	unsigned int block_nb;
	unsigned int new_len, rem_len, tmp_len;
	const unsigned char *shifted_message;
	tmp_len = SHA224_256_BLOCK_SIZE - m_len;
	rem_len = len < tmp_len ? len : tmp_len;
	memcpy(&m_block[m_len], message, rem_len);
	if (m_len + len < SHA224_256_BLOCK_SIZE) {
		m_len += len;
		return;
	}
	new_len = len - rem_len;
	block_nb = new_len / SHA224_256_BLOCK_SIZE;
	shifted_message = message + rem_len;
	transform(m_block, 1);
	transform(shifted_message, block_nb);
	rem_len = new_len % SHA224_256_BLOCK_SIZE;
	memcpy(m_block, &shifted_message[block_nb << 6], rem_len);
	m_len = rem_len;
	m_tot_len += (block_nb + 1) << 6;
}

void SHA256::final(unsigned char *digest)
{
	unsigned int block_nb;
	unsigned int pm_len;
	unsigned int len_b;
	int i;
	block_nb = (1 + ((SHA224_256_BLOCK_SIZE - 9)
					 < (m_len % SHA224_256_BLOCK_SIZE)));
	len_b = (m_tot_len + m_len) << 3;
	pm_len = block_nb << 6;
	memset(m_block + m_len, 0, pm_len - m_len);
	m_block[m_len] = 0x80;
	SHA2_UNPACK32(len_b, m_block + pm_len - 4);
	transform(m_block, block_nb);
	for (i = 0; i < 8; i++) {
		SHA2_UNPACK32(m_h[i], &digest[i << 2]);
	}
}

std::string sha256(std::string input)
{
	unsigned char digest[SHA256::DIGEST_SIZE];
	memset(digest, 0, SHA256::DIGEST_SIZE);

	SHA256 ctx = SHA256();
	ctx.init();
	ctx.update((unsigned char*)input.c_str(), input.length());
	ctx.final(digest);

	char buf[2 * SHA256::DIGEST_SIZE + 1];
	buf[2 * SHA256::DIGEST_SIZE] = 0;
	for (int i = 0; i < SHA256::DIGEST_SIZE; i++)
		sprintf(buf + i * 2, "%02x", digest[i]);
	return std::string(buf);
}

std::string sha256(std::vector<char>& input) {
	unsigned char digest[SHA256::DIGEST_SIZE];
	memset(digest, 0, SHA256::DIGEST_SIZE);

	SHA256 ctx = SHA256();
	ctx.init();
	ctx.update((unsigned char*)input.data(), input.size());
	ctx.final(digest);

	char buf[2 * SHA256::DIGEST_SIZE + 1];
	buf[2 * SHA256::DIGEST_SIZE] = 0;
	for (int i = 0; i < SHA256::DIGEST_SIZE; i++)
		sprintf(buf + i * 2, "%02x", digest[i]);
	return std::string(buf);
}

#endif

