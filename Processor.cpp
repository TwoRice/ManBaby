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

bool* Processor::getCI(){

	return ci;

}

void Processor::setPI(bool instruction[32]){

	for(int i = 0; i < 32; i++){

		pi[i] = instruction[i];

	}

}

/**
*Method which resets each element of ci[] to 0
*
*/
void Processor::resetCI(){

	for (int i = 0; i < 32; i++)
	{
		ci[i] = 0;
	}

}

/**
*Method which converts binary array into decimal integer
*
*param a: bool binary[] - binary array for conversion
*return : int decimal	- binary array converted to integer
*/
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

int Processor::twosComp(bool operand[32]){

	int first1;

	if(operand[31] == 0){

		
		return convertBinToDec(operand, 32);

	}

	else{

		for(int i = 0; i < 32; i++){

			if(operand[i] == 1){

				first1 = i;
				break;

			}

		}

		for(int i = 31; i > first1; i--){

			operand[i]==0 ? 1 : 0;			

		}

		return (-1 * convertBinToDec(operand, 32));

	}

}

/**
*Method which converts ci[] into decimal, increments the result
*and finally, converts the decimal integer back into ci[] 
*
*/
void Processor::increment(){

	int decimal = convertBinToDec(ci,32);
	decimal++;
	*ci = convertDecToBin(decimal);
	
}

int Processor::getOp(int start, int end){

	int size = (end-start)+1;
	bool operand[size];

	for(int i= start; i < (end+1); i++){

		operand[i] = pi[i];

	}

	int memLoc = convertBinToDec(operand,size);

	return memLoc;

}
	
