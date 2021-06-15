#include <iostream>
#include<string> 
#include <random>
#include <fstream>
#include <stdlib.h>

using namespace std;

#include "GolombEncoder.h"
#include "GolombDecoder.h"
#include "DataGenerator.h"
#include "TxtLoader.h"

#define BUFFER_SIZE 1024

#define DIST_PATH "/Users/marta/workspace/KODA/exp-golomb/obrazy/peppers.txt"

int main (int argc, char *argv[]) 
{
	if(argc > 1){
        TxtLoader loader;
        vector<int> data = loader.read(DIST_PATH);
		
		DataGenerator dataGenerator;
		
		char * char_m = argv[1];
		uint64_t m;
		m = strtoull(char_m, NULL, 0);
		
		uint8_t buffer[BUFFER_SIZE];
		
		GolombEncoder expGolomb(m);
		expGolomb.setBuffer(buffer, BUFFER_SIZE);
				
		for(auto &item: data) {
              // std::cout <<"item"<< item << std::endl;
              expGolomb.encode(item);
        }
		
		expGolomb.close();
		
				
		GolombDecoder expDecoder(m);
		expDecoder.setBuffer(buffer, BUFFER_SIZE);

		uint64_t a;
		//pętla dekodująca buffer
		cout<<"Wyniki dekodowania"<<endl;
		for (auto &item: data) {
		expDecoder.decode(a);
		cout << a << " "<< item << endl;
		}

		
	}
	else{
		cout << "Wprowadź parametr m." << endl;
	}
	
	
	return 0;
}
