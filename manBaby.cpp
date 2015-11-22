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
		void jmp(int operand);
		void jrp(int operand);
		void ldn(int operand);
		void sto(int operand);
		void sub(int operand);
		void cmp();
		void stp();
		void fetch();
		void decode();
		void execute(int opcode, int operand);


};

void ManBaby::loadProgramToMemory(){

	string fileName;
	cout << "Enter Filename (Without Extension): " << endl;
	getline(cin, fileName);
	fileName.append(".txt");
	theStore.loadProgram(fileName);


}

/**
*Method which jumps to the instruction at the address obtained from the specific memory address
*
*param a: int operand - integer to be used for operation
*/
void ManBaby::jmp(int operand){

	theProcessor.setCI(theStore.readMemory(operand));

}

/**
*Method which jumps to the instruction at the program counter + the relative value obtained from the specified memory address
*
*param a: int operand - integer to be used for operation
*/
void ManBaby::jrp(int operand){

	int ciInt = theProcessor.convertBinToDec(theProcessor.getCI(), 32);
	int memStore = theProcessor.convertBinToDec(theStore.readMemory(operand), 32);
	ciInt += memStore;
	theProcessor.setCI(theProcessor.convertDecToBin(ciInt));

}

/**
*Method which takes the number from the specified memory address _!_
*
*param a: int operand - integer to be used for operation
*/
void ManBaby::ldn(int operand){

	theProcessor.setAccumulator(theProcessor.negate(theStore.readMemory(operand)));

}

/**
*Method which stores the number in the accumulator to the specified memory address _!_
*
*param a: int operand - integer to be used for operation
*/
void ManBaby::sto(int operand){

	theStore.writeMemory(operand, theProcessor.getAccumulator());

}

/**
*Method which subtracts the number at the specified memory address _!_ from the value in the accumulator
*and then stores the result in the accumulator
* 
*param a: int operand - integer to be used for operation
*/
void sub(int operand){

	int accuDecimal = theProcessor.convertBinToDec(accumulator, 32);
	int memStore = theProcessor.convertBinToDec(theStore.readMemory(operand)); 
	accuDecimal -= memStore;
	accumulator = theProcessor.setAccumulator(theProcessor.convertDecToBin(accuDecimal));
}

/**
*Method which skips the next instruction if the accumulator contains a negative number
*
*/
void cmp(){

	int accuDecimal = theProcessor.convertBinToDec(accumulator, 32);	

			if(accuDecimal < 0){
				theProcessor.increment();
			}
}

/**
*Method which stops the program
*
*param a: int operand - integer to be used for operation
*/
void ManBaby::stp(int operand){

	

}

void ManBaby::fetch(){

	int memoryAddress;

	memoryAddress = theProcessor.convertBinToDec(theProcessor.getCI(),32);
	theProcessor.increment();
	theProcessor.setPI(theStore.readMemory(memoryAddress));

}

void ManBaby::decode(){

	int operand;
	int opcode;
	bool* binNum;
	int num;

	operand = theProcessor.getOp(0, 4);
	opcode = theProcessor.getOp(13, 15);
	
	binNum = theStore.readMemory(operand);
	operand = theProcessor.convertBinToDec(binNum, 32);

	//execute(opcode, operand);

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
				theBaby.decode();

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
