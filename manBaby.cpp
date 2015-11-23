/**
*Program to simulate the hardware of the Manchester Baby which is able to take txt files of machine
*code and execute them
* 
*Authors : Rory Magowan, Daniel Bereton, Daniel Kinnaird
*Version : 1.0 22nd November 2015
*
*/
#include <iostream>
#include <string>
#include <sstream>
#include "Processor.cpp"
#include "Store.cpp"

using namespace std;


/**
*Class which for the Manchester Baby which contains the processor and the store and the functions
*they require to perform the fetch execute cycle
*
*/
class ManBaby{

	private :

		//Object for the processor
		Processor theProcessor;
		//Object for the store (memory)
		Store theStore;

	public : 
		
		void printCI();
		void printPI();
		void printAcc();
		void printStore();
		void printStoreLine(int operand);
		bool loadProgramToMemory();	
		void jmp(int operand);
		void jrp(int operand);
		void ldn(int operand);
		void sto(int operand);
		void sub(int operand);
		void cmp();
		void fetch();
		bool decode();
		bool execute(int opcode, int operand);
		void run();


};

/**
*Method to print the contents of the CI (Control Instruction)
*
*/
void ManBaby::printCI(){

	cout << "CI : ";
	for(int i = 0; i < 32; i++){

		cout << theProcessor.getCI()[i];

	}
	cout << endl;


}

/**
*Method to print the contents of the PI (Present Instruction)
*
*/
void ManBaby::printPI(){

	cout << "PI : ";
	for(int i = 0; i < 32; i++){

		cout << theProcessor.getPI()[i];

	}
	cout << endl;


}

/**
*Method to print the contents of the Accumulator
*
*/
void ManBaby::printAcc(){

	cout << "Accumulator : ";
	for(int i = 0; i < 32; i++){

		cout << theProcessor.getAccumulator()[i];

	}
	cout << endl;


}

/**
*Method to print the contents of the store (memory)
*
*/
void ManBaby::printStore(){

	cout << "Store : " << endl;
	
	for(int j = 0; j < 32; j++){

		for(int i = 0; i < 32; i++){

			cout << theStore.readMemory(j)[i];

		}
		cout << endl;

	}

}

/**
*Method to print the contents of the a given line of memory in the store (memory)
*
*param : operand - the memory location for the line of memory to be printed
*/
void ManBaby::printStoreLine(int operand){

	cout << "Value at Store : ";
	for(int i = 0; i < 32; i++){

		cout << theStore.readMemory(operand)[i];

	} 
	cout << endl;

}

/**
*Method to take the file name of for the txt file containing the machine code to be executed and
*then load the contents of said file into the stoe (memory)
*
*return : whether or not the file entered by the user exists or not
*/
bool ManBaby::loadProgramToMemory(){

	string fileName;
	bool exists;

	cout << "Enter Filename (Without Extension): " << endl;
	getline(cin, fileName);
	//adds the files extension to the file name
	fileName.append(".txt");
	exists = theStore.loadProgram(fileName);
	if(exists){

		theProcessor.resetCI();
		theProcessor.resetAccumulator();
		printStore();
		cout << endl;
		return true;

	}

	else{

		return false;

	}


}

/**
*Method which jumps to the instruction at the address obtained from the specific memory address
*by setting the CI to the value stored at said address
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
*Method which takes the number from the specified memory address and puts it into the accumulator
*
*param a: int operand - integer to be used for operation
*/
void ManBaby::ldn(int operand){

	theProcessor.setAccumulator(theProcessor.negate(theStore.readMemory(operand)));

}

/**
*Method which stores the number in the accumulator at the specified memory address
*
*param a: int operand - integer to be used for operation
*/
void ManBaby::sto(int operand){

	theStore.writeMemory(operand, theProcessor.getAccumulator());

}

/**
*Method which subtracts the number at the specified memory address from the value in the accumulator
*and then stores the result in the accumulator
* 
*param a: int operand - integer to be used for operation
*/
void ManBaby::sub(int operand){

	int accuDecimal = theProcessor.convertBinToDec(theProcessor.getAccumulator(), 32);
	int memStore = theProcessor.convertBinToDec(theStore.readMemory(operand), 32); 
	accuDecimal -= memStore;
	theProcessor.setAccumulator(theProcessor.convertDecToBin(accuDecimal));
}

/**
*Method which skips the next instruction if the accumulator contains a negative number
*
*/
void ManBaby::cmp(){

	int accuDecimal = theProcessor.convertBinToDec(theProcessor.getAccumulator(), 32);	

			if(accuDecimal < 0){
				theProcessor.increment();
			}

}


/**
*Method which fetches the present instruction from the store (memory)
*
*/
void ManBaby::fetch(){

	int memoryAddress;

	printCI();
	theProcessor.increment();
	memoryAddress = theProcessor.convertBinToDec(theProcessor.getCI(),32);
	printCI();
	theProcessor.setPI(theStore.readMemory(memoryAddress));
	printPI();

}

/**
*Method which extratcs the operand and opcode from the presnet instruction and uses them for the
*execute method
*
*return - whether or not the program has finished
*/
bool ManBaby::decode(){

	int operand;
	int opcode;
	int num;

	cout << "Operand : ";
	//Gets the operand as the first 5 values in the present instruction
	operand = theProcessor.getOp(0, 4);
	cout << "Opcode : ";
	//Gets the opcode as the values from position 13 to position 15 in the present instrcution
	opcode = theProcessor.getOp(13, 15);
	cout << endl;

	execute(opcode, operand);

}

/**
*Method which uses ths decoded instruction to execute the instruction
*
*return - whether or not the program has finished
*/
bool ManBaby::execute(int opcode, int operand){

	switch(opcode){

		case 0 :

			cout << "JMP" << endl;
			jmp(operand);
			printStoreLine(operand);
			printCI();
			cout << endl;
			break;

		case 1 : 

			cout << "JRP" << endl;
			printCI();
			jrp(operand);
			printStoreLine(operand);
			printCI();
			cout << endl;
			break;

		case 2 : 

			cout << "LDN" << endl;
			ldn(operand);
			printStoreLine(operand);	
			printAcc();	
			cout << endl;
			break;	

		case 3 : 
		
			cout << "STO" << endl;
			sto(operand);
			printAcc();	
			printStoreLine(operand);	
			cout << endl;
			break;

		case 4 : 
		
			cout << "SUB" << endl;
			printAcc();
			printStoreLine(operand);
			sub(operand);
			printAcc();
			cout << endl;
			break;	
			
		case 5 : 
		
			cout << "SUB" << endl;
			printAcc();
			printStoreLine(operand);
			sub(operand);
			printAcc();
			sub(operand);
			cout << endl;
			break;	
			
		case 6 : 
		
			cout << "CMP" << endl;
			printAcc();
			printCI();
			cmp();
			printCI();
			break;	
			
		case 7 : 
		
			cout << "STP" << endl;
			cout << "Program Terminated" << endl;
			cout << endl;
			return false;
			break;

		default : 
		
			cout << "Error in Machine Code, opcode does not exist" << endl;
			break;										


	}

}

/**
*Method to load the program into memeory then run the fetch execute cycle until the stop instruction
*is given
*
*/
void ManBaby::run(){

	bool run;
	
	if(loadProgramToMemory()){
		do{
			fetch();
			run = decode();
		}while(run);
	}	

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
* Displays a basic text menu to the user
*
*/
void displayMenu(){

	cout << "(1) Load Program" << endl;
	cout << "(2) Exit" << endl;
}

/**
*Method to handle the user selection for the menu
*
*/
void menu(){
	
	ManBaby theBaby;
	int option;

	do
	{

		displayMenu();
		cout << "Enter an Option: ";
		option = readInt();

		switch(option){

			case 1:
				
				theBaby.run();

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
*Main method where the program is run from 
*
*/
int main(){

 	menu();

	return 0;



}
