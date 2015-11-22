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

/**
*Method which
*
*/
void Processor::setAccumulator(bool accumulator[]){

	for(int i = 0; i < 32; i++){

		this -> accumulator[i] = accumulator[i];

	}

}

/**
*Method which
* 
*/
bool* Processor::getAccumulator(){

	return accumulator;

}


/**
* Method which 
*
*param a : bool memoryaddress[32] 
*/
void Processor::setCI(bool memoryAddress[32]){

	for (int i = 0; i < 32; i++)
	{
		ci[i] = memoryAddress[i];
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

bool* Processor::getPI(){

	return pi;

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

	if(length != 32 || binary[31] == 0){

		for (int i = length - 1; i >= 0; i--){

			decimal += (int(binary[i]))*pow(2,i);

		}

	}

	else{

		decimal = -1 * ((int(binary[31]))*pow(2,31));

		for (int i = 30; i >= 0; i--){

			decimal += (int(binary[i]))*pow(2,i);

		}

	}

	return decimal;

}

/**
*Method which converts decimal integer into binary array
*
*param a: int decimal - decimal number for conversion
*return : array[]	  - decimal number converted to binary
*/
bool* Processor::convertDecToBin(int decimal){

	bool static array[32]; 
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

bool* Processor::negate(bool operand[32]){

	int first1;

	for(int i = 0; i < 32; i++){

		if(operand[i] == 1){

			first1 = i;
			break;

		}

	}

	for(int i = 31; i > first1; i--){

		operand[i]==0 ? 1 : 0;			

	}

	return operand;

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
