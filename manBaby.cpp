#include <iostream>
#include <string>
#include <sstream>
#include "Processor.cpp"
#include "Store.cpp"

using namespace std;


class ManBaby{

	private :

		Processor theProcessor;
		Store theStore;

	public : 
		
		void loadProgramToMemory();	
		void fetch();
		void decode();


};

void ManBaby::loadProgramToMemory(){

	string fileName;
	cout << "Enter Filename (Without Extension): " << endl;
	getline(cin, fileName);
	fileName.append(".txt");
	theStore.loadProgram(fileName);


}

void ManBaby::fetch(){

	int memoryAddress;

	memoryAddress = theProcessor.convertBinToDec(theProcessor.getCI(),32);
	theProcessor.increment();
	theProcessor.setPI(theStore.readMemory(memoryAddress));
	cout << memoryAddress << endl;

}

void ManBaby::decode(){

	int operand;
	int opcode;
	int twosCompNum;
	bool num[32];

	operand = theProcessor.getOp(0, 4);
	opcode = theProcessor.getOp(13, 15);
	
	num = theStore.readMemory(operand);
	twosCompNum = theProcessor.twosComp(num);

}

//////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////


/**
*Method which validates if what is entered by the user is an integer
*
*return : myInt - integer value entered by the user
*/
int readInt(){

	string input;
	int myInt;

	while (true){

		getline(cin, input);

		stringstream stream(input);
		if (stream >> myInt){
			break;
		}
		cout << "Please only enter an integer value" << endl;
	}

	return myInt;

}


/**
* 
*/
void displayMenu(){

	cout << "(1) Load Program" << endl;
	cout << "(2) Exit" << endl;
}

void menu(){
	
	ManBaby theBaby;
	int option;

	do
	{

		displayMenu();
		cout << "Enter an Option: ";
		option = readInt();

		switch(option){
			//Option 1: Calls the loadfile method -
			//loadfile() .....................
			case 1:
				
				theBaby.loadProgramToMemory();
				theBaby.fetch();

				break;

			case 2:
				cout << "Exiting Program" << endl;

				break;

			default:
				cout << "Invalid Option" << endl;

				break;

		}


	}
	while(option != 2);
}

/**
* 
*/
int main(){

 	menu();

	return 0;



}
