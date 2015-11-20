#include <iostream>
#include <cmath>
#include <algorithm>
#include "Processor.h"

using namespace std;

Processor::Processor(){

	for (int i = 0; i < 32; i++)
	{
		accumulator[i] = 0;
		ci[i] = 0;
		pi[i] = 0;
	}

}

void Processor::resetCI(){

	for (int i = 0; i < 32; i++)
	{
		ci[i] = 0;
	}

}

int Processor::convertBinToDec(bool binary[], int length){

	int decimal = 0;

		for (int i = length - 1; i >= 0; i--)
		{
			decimal += (int(binary[i]))*pow(2,i);
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

void Processor::increment(){

	int decimal = convertBinToDec(ci,32);
	decimal++;
	*ci = convertDecToBin(decimal);
	
}

int Processor::fetchOperand(){

	bool operand[5];

	for(int i= 0; i < 5; i++){

		operand[i] = pi[i];

	}

	int memLoc = convertBinToDec(operand,5);

	return memLoc;

}
	
