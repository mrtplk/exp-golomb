#include <iostream>
#include <fstream>
using namespace std;

class TxtLoader
{
public:

	TxtLoader();

	void read(const char* path);

	void writeText(const char* path, string text);

	void writeBits(const char* path, char* text);

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

void TxtLoader::writeText(const char* path, string text)
{
	ofstream myfile;
  	myfile.open (path, ios::out | ios::app | ios::ate);
  	myfile << text << " ";
  	myfile.close();
}