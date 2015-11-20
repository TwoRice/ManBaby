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

/**
*Method which resets each element of ci[] to 0
*
*/
void Processor::resetCI(){

	for (int i = 0; i < 32; i++)
	{
		bool ci[i] = 0;
	}

}

/**
*Method which converts binary array into decimal integer
*
*param a: bool binary[] - binary array for conversion
*return : int decimal	- binary array converted to integer
*/
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

/**
*Method which converts decimal integer into binary array
*
*param a: int decimal - decimal number for conversion
*return : array[]	  - decimal number converted to binary
*/
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

/**
*Method which converts ci[] into decimal, increments the result
*and finally, converts the decimal integer back into ci[] 
*
*/
void increment(){

		int decimal = convertBinToDec(ci);
		decimal++;
		ci = convertDecToBin(decimal);
}

int Processor::fetchOperand(){

	bool operand[5];

	for(int i= 0; i < 5; i++){

		operand[i] = pi[i];

	}

	int memLoc = converToDec(operand);

	return memLoc;

}
	
