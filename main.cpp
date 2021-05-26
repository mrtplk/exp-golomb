#include <iostream>
#include<string> 
#include <random>
#include <fstream>

using namespace std;

#include "GolombEncoder.h"
#include "GolombDecoder.h"
#include "DataGenerator.h"
#include "TxtLoader.h"

#define BUFFER_SIZE 1024

int main (int argc, char *argv[]) 
{
	if(argc > 1){
		
		DataGenerator dataGenerator;
		
		char * char_m = argv[1];
		uint64_t m;
		m = strtoull(char_m, NULL, 0);
		
		uint8_t buffer[BUFFER_SIZE];
		
		GolombEncoder expGolomb(m);
		expGolomb.setBuffer(buffer, BUFFER_SIZE);
		
		int p[14]={};
		
		/*pętla generująca kolejne liczby z rozkładem normalnym oraz kodująca je; 
		przechowywane są w buffer*/
		for (int i = 0; i < 100; i++) {
		int number = dataGenerator.NormDist(100, 10);
		if ((number>=30)&&(number<170)) ++p[int((number-30)/10)];
		expGolomb.encode(number);
		}
		
		cout<<"Histogram danych wejściowych"<<endl;
		for (int i=0; i<14; ++i) {
    		cout << i*10+30 << "-" << ((i+1)*10+30) << ": ";
    		cout << string(p[i],'*') << endl;
  		}
		
		expGolomb.close();
		
				
		GolombDecoder expDecoder(m);
		expDecoder.setBuffer(buffer, BUFFER_SIZE);

		uint64_t a;
		//pętla dekodująca buffer
		cout<<"Wyniki dekodowania"<<endl;
		for (int i = 0; i < 100; i++) {
		expDecoder.decode(a);
		cout << a << endl;
		}

		
	}
	else{
		cout << "Wprowadź parametr m." << endl;
	}
	
	
	return 0;
}