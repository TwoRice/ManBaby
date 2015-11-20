#include <iostream>
#include <cmath>
#include <algorithm>
#include "Processor.h"

using namespace std;

Processor::Processor(){

	for (int i = 0; i < 32; i++)
	{
		bool accumulator[i] = 0;
		bool ci[i] = 0;
		bool pi[i] = 0;
	}

}

void Processor::resetCI(){

	for (int i = 0; i < 32; i++)
	{
		bool ci[i] = 0;
	}

}

int Processor::convertBinToDec(bool binary[]){

int decimal = 0;
int length = binary.length();

	for (int i = length - 1; i >= 0 i--)
	{
		decimal += (int(binary[i]) -48)*pow(2,i);
	}

cout << "Conversion of Binary to Decimal complete" << endl;
cout << decimal << endl;
return decimal;

}

bool* Processor::convertDecToBin(int decimal){

bool array[32]; 
int index = 0;

	for (int i = 0; i < 32; i++)
	{
		array[i] = 0;
	}

	while(decimal !=0){
			
			array[index] = decimal%2;
			decimal/=2;
			index++;
	}
	
return array;
}

void increment(){

		int decimal = convertBinToDec(ci);
		decimal++;
		ci = convertDecToBin(decimal);
	
//take CI[]
	//convert to Dec
	//increment
	//convert back to Bin
	//place Bin back in CI[]
}
	
