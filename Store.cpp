#include <iostream>
#include <string>
#include <fstream>

#include "Store.h"

using namespace std;

Store::Store(){

	for(int i = 0; i < 32; i++){

		for(int j = 0; j < 32; j++){

			memory[i][j] = 0;

		}

	}
}

void Store::loadProgram(string fileName){

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

	}

	else{

		cout << "File does not exist" << endl;

	}

}
