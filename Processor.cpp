/**
*Authors : Rory Magowan, Daniel Bereton, Daniel Kinnaird
*Version : 1.0 22nd November 2015
*
*/
#include <iostream>
#include <cmath>
#include <algorithm>
#include "Processor.h"

using namespace std;

/**
*Constructor for the processor which sets the contents of the CI, PI and accumulator to all 0s
*
*/
Processor::Processor(){

	for (int i = 0; i < 32; i++)
	{
		accumulator[i] = 0;
		ci[i] = 0;
		pi[i] = 0;
	}

}

/**
*Setter Method for the Accumulator
*
*/
void Processor::setAccumulator(bool accumulator[]){

	for(int i = 0; i < 32; i++){

		this -> accumulator[i] = accumulator[i];

	}

}

/**
*Getter Method for the Accumulator
* 
*/
bool* Processor::getAccumulator(){

	return accumulator;

}


/**
*Setter Method for the CI
*
*/
void Processor::setCI(bool memoryAddress[32]){

	for (int i = 0; i < 32; i++)
	{
		ci[i] = memoryAddress[i];
	}

}

/**
*Getter Method for the CI
*
*/
bool* Processor::getCI(){

	return ci;

}

/**
*Setter Method for the PI
*
*/
void Processor::setPI(bool instruction[32]){

	for(int i = 0; i < 32; i++){

		pi[i] = instruction[i];

	}

}

/**
*Getter Method for the PI
*
*/
bool* Processor::getPI(){

	return pi;

}

/**
*Method which resets each element of ci to 0
*
*/
void Processor::resetCI(){

	for (int i = 0; i < 32; i++)
	{
		ci[i] = 0;
	}

}

/**
*Method which resets each element of the accumulator to 0
*
*/
void Processor::resetAccumulator(){

	for (int i = 0; i < 32; i++)
	{
		accumulator[i] = 0;
	}	

}

/**
*Method which converts a twos complement binary number into a decimal integer
*
*param a: bool binary[] - binary array for conversion
*return : int decimal	- binary array converted to integer
*/
int Processor::convertBinToDec(bool binary[], int length){

	int decimal = 0;

	//Checks if the binary number is less than 32 bits long (ie. an operand or opcode which aren't
	//two's complement numbers or if the number begins with a 0 and therefore is positive
	if(length != 32 || binary[31] == 0){

		for (int i = length - 1; i >= 0; i--){

			decimal += (int(binary[i]))*pow(2,i);

		}

	}

	else{

		//If the number begins with one the MSB (most signifigant bit) calcualted as a negative
		//value
		decimal = -1 * ((int(binary[31]))*pow(2,31));

		for (int i = 30; i >= 0; i--){

			decimal += (int(binary[i]))*pow(2,i);

		}

	}

	return decimal;

}

/**
*Method which converts decimal integer into binary number
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

/**
*Method which flips all the bits after the first 1 (read from right to left)
*
*param : operand - The binary number to be negated
*return : operand - The negated binary number
*
*/
bool* Processor::negate(bool operand[32]){

	int first1;

	//For loop to find the first 1 in the binary number
	for(int i = 0; i < 32; i++){

		if(operand[i] == 1){

			first1 = i;
			break;

		}

	}

	for(int i = 31; i > first1; i--){

		//Condition operator used to flip the bits
		operand[i]==0 ? operand[i]=1 : operand[i]=0;			

	}

	return operand;

}

/**
*Method which converts ci into decimal, increments the result
*and finally, converts the decimal integer back into ci 
*
*/
void Processor::increment(){

	int decimal = convertBinToDec(ci,32);
	decimal++;
	setCI(convertDecToBin(decimal));
	
}

/**
*Method to get a sub array from the present instruction used to get the operand and opcode from
*the present instruction
*
*param : start - the start position for the sub array in present instruction
*param :  end - the end position for the sub array in present instruction
*return : decOP - the decimal value for the operand or opcode taken from the present instruction
*/
int Processor::getOp(int start, int end){

	int size = (end-start)+1;
	bool op[size];
	int j = 0;

	for(int i= start; i < (end+1); i++){

		op[j] = pi[i];
		cout << op[j];
		j++;


	}
	cout << endl;

	int decOP = convertBinToDec(op,size);

	return decOP;

}
