#include <iostream>
#include <string>
#include <sstream>
#include "Processor.cpp"
#include "Store.cpp"

using namespace std;


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
Store loadFile(Store theStore){

	string fileName;
	cout << "Enter Filename (Without Extension): " << endl;
	getline(cin, fileName);
	fileName.append(".txt");
	theStore.loadProgram(fileName);

	return theStore;

}

/**
* 
*/
void displayMenu(){

	cout << "(1) Load Program" << endl;
	cout << "(2) Exit" << endl;
}

void menu(){
	
	Processor theProcessor;
	Store theStore;
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
				theStore = loadFile(theStore);

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
