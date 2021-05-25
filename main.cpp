#include <iostream>
#include <random>
#include <fstream>

using namespace std;

#include "GolombEncoder.h"
#include "GolombDecoder.h"

static const int length = 50000;
static const int  max = 20;

int main (int argc, char *argv[]) 
{
	if(argc > 2){
		char * char_m = argv[1];
		uint64_t m;
		m = strtoull(char_m, NULL, 0);
		//cout << m << endl;
		uint8_t buffer[1024];
		
		GolombEncoder expGolomb(m);
		expGolomb.setBuffer(buffer, 1024);
		
		expGolomb.encode(2);
		expGolomb.encode(1);
		expGolomb.encode(3);
		expGolomb.encode(7);
		
		expGolomb.close();
		
		GolombDecoder expDecoder(m);
		expDecoder.setBuffer(buffer, 1024);

		uint64_t a;
		expDecoder.decode(a);
		cout << a << endl;
		expDecoder.decode(a);
		cout << a << endl;
		expDecoder.decode(a);
		cout << a << endl;
		expDecoder.decode(a);
		cout << a << endl;
		
	}
	else{
		cout << "Wprowadź parametry: (1) m  (2) ciąg do zakodowania." << endl;
	}
	
	
	return 0;
}