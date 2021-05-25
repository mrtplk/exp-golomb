#include <stdio.h>
#include <math.h>
#include <iostream>

using namespace std;

int g(int x, int m){
	int result = floor(log2(x/pow(2, m)+1));
	float a = floor(log2(x/pow(2, m)+1));
	//printf("%f\n",a);
	//printf("%d\n",result);
	return result;
}

int r(int x, int m, int g){
	float sum = 0.0;
	for(int i=0; i<g; i++){
		sum+=pow(2,i+m);
	}
	//printf("%f\n",sum);
	int result = x - sum;
	//printf("%d\n",result);
	return result;
}

//Unary coding is a simple method that can only encode non-negative integers. 
//For any non-negative integer num, its unary encoding is num 1 followed by a 0

void unary_encode(int n){
	while(n>0){
		//WriteBit(1);
		printf("1");
		n--;
	}
	//WriteBit(0);
	printf("0\n");
}

int unary_decode(){
	int n = 0;
	while(n>0){ //TO DO
		//WriteBit(1);
		n++;
	}
	//WriteBit(0);
	//printf("0\n");
	return n;
}


int main(){
	unary_encode(3);
	int m = 3;
	int g_0 = g(14, m);
	r(14, m, g_0);
	int g_1 = g(1, m);
	r(0, m, g_1);
	int g_2 = g(2, m);
	r(0, m, g_2);
	g(3, m);
	g(4, m);
	g(5, m);
	g(6, m);
	g(7, m);
	g(8, m);
	g(9, m);
	g(10, m);
	cout.flush();
	return 0;
}