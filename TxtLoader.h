#include <iostream>
#include <fstream>
#include "BitStream.h"

using namespace std;

class TxtLoader
{
public:

	TxtLoader();

	void read(const char* path);
	
	void readBits(const char* path, uint8_t buffer[]);

	void writeText(const char* path, string text);

	void writeBits(const char* path, uint8_t buffer[]);

private:
};

TxtLoader::TxtLoader()
{
}

void TxtLoader::read(const char* path)
{
	fstream my_file;
	my_file.open(path, ios::in);
	if (!my_file) {
		cout << "No such file" << endl;

	}
	char ch;
	while (1) {
		my_file >> ch;
		if (my_file.eof())
			break;
		cout << ch;
	}
	my_file.close();
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