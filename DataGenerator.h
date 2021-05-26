#pragma once
#include <random>
#include <math.h>  

static std::random_device __randomDevice;
static std::mt19937 __randomGen(__randomDevice());


class DataGenerator
{
public:

	DataGenerator();

	int LaplDist(int scale);

	int UniDist(int a, int b);
	
	int NormDist(int mean, int std);
	
private:
	int ExpDist(int mean);
};

DataGenerator::DataGenerator()
{
}

int DataGenerator::NormDist(int mean, int std)
{
    int val = -1;
    std::normal_distribution<float> distribution(mean, std);
    do { val = distribution(__randomGen); } 
    while(val < 0 || val > 100);
    return val;
}

int DataGenerator::ExpDist(int mean)
{
	//return -mean*log(rand());
	std::exponential_distribution<float> distribution(mean);
	int val = -1;
	do { val = distribution(__randomGen); distribution.reset();} 
    while(val < 0 || val > 10);
    return val;
}

int DataGenerator::LaplDist(int scale)
{
	int e1, e2 = -1;
	while(e1 == e2){
	e1 = ExpDist(scale);
    e2 = ExpDist(scale);
    }
    return e1 - e2;
}
int DataGenerator::UniDist(int a, int b)
{
	return rand() % (b-a+1)  + a;
}

