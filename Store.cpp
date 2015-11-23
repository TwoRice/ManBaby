/**
*Authors : Rory Magowan, Daniel Bereton, Daniel Kinnaird
*Version : 1.0 22nd November 2015
*
*/
#include <iostream>
#include <string>
#include <fstream>

#include "Store.h"

using namespace std;

/**
*Constructor to initialise the Store to all 0s
*
*/
Store::Store(){

	for(int i = 0; i < 32; i++){

		for(int j = 0; j < 32; j++){

			memory[i][j] = 0;

		}

	}
}

/**
*Method to read a line of memory from a specified address
*
*param : location - the memory addres to be read from 
*return : data - the binary number stored at the specified memory address
*/
bool* Store::readMemory(int location){

	//Static array for the data held at the memory location so that it is not destroyed when the
	//function terminates
	bool static data[32];

	for(int i = 0; i < 32; i++){

		data[i] = memory[location][i];

	}

	return data;

}

/**
*Method to write to a specific memory address
*
*param : location - the memory address to be written to
*param : data - the data to be written to the address
*/
void Store::writeMemory(int location, bool data[32]){

	for(int i = 0; i < 32; i++){

		memory[location][i] = data[i];

	}

}

/**
*Method to load the machine code from a text filme into the store
*
*param : fileName - the name of the file to be read from
*return whether or not the file existed
*/
bool Store::loadProgram(string fileName){

	ifstream reader;
	string nextLine;

	reader.open(fileName.c_str());

	if(reader.is_open()){

		int j = 0;

		while(!reader.eof()){

			getline(reader, nextLine);
			for(int i = 0; i < nextLine.length(); i++){

				memory[j][i] = nextLine.at(i) - '0';

			}

			j++;

		}

		return true;

	}

	else{

		cout << "File does not exist" << endl;
		return false;

	}

}
