#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <iterator>
#include <algorithm>
#include <vector>
#include "BitStream.h"

using namespace std;

/*max size of an image*/
#define MAX 800

template<typename T>
std::vector<T> parse_stream(std::istream &stream) {
    std::vector<T> v;
    std::istream_iterator<T> input(stream);
    std::copy(input, std::istream_iterator<T>(), std::back_inserter(v));
    return v;
}

class TxtLoader
{
public:

	TxtLoader();

	vector<int> read(const char* path);
	
	void readBits(const char* path, uint8_t buffer[]);

	void writeText(const char* path, string text);

	void writeBits(const char* path, uint8_t buffer[]);
    

private:
};

TxtLoader::TxtLoader()
{
}

vector<int> TxtLoader::read(const char* path)
{
  std::ifstream input(path);
  std::vector<int> v;
  std::string line;
  while (getline(input, line)) {
      stringstream lineStream(line);
      int value;
      while(lineStream >> value){
          v.push_back(value);
      }
  }
    
  input.close();
  return v;
}

void TxtLoader::readBits(const char* path, uint8_t buffer[])
{
	fstream my_file;
	my_file.open(path, ios::in | ios::binary);
	if (!my_file) {
		cout << "No such file" << endl;

	}
	char ch;
	int i = 0;
	while (1) {
		my_file >> ch;
		if (my_file.eof())
			break;
			
		buffer[i] = ch;
		i++;
		//cout << std::bitset<8>(ch);
	}
	my_file.close();
}

void TxtLoader::writeText(const char* path, string text)
{
	ofstream myfile;
  	// myfile.open (path, ios::out | ios::app | ios::ate);
  	myfile.open (path, ios::out | ios::ate);
  	myfile << text << " ";
  	myfile.close();
}

void TxtLoader::writeBits(const char* path, uint8_t buffer[])
{
	/*
	bool b;
	uint64_t groupID = 0;

	// group id
	b = bitStream.getBit();
	while (!b)
	{
		groupID++;
		b = bitStream.getBit();
	}

	// groupID-1bit
	std::bitset<64> bits;
	bits.reset();
	for (int i = 0; i < groupID; i++)
	{
		b = bitStream.getBit();
		bits.set(i, b);
	}
	
	*/
	ofstream myfile;
  	// myfile.open (path, ios::out | ios::app | ios::ate | ios::binary);
  	myfile.open (path, ios::out | ios::ate | ios::binary);
  	for(int i= 0; i<sizeof(buffer); i++ )
  	{
  		myfile.write((char*)&buffer[i],sizeof(buffer[i]));
  	}
  	myfile.close();
  	
}

