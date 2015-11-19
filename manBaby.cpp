#include <iostream>
#include <string>
#include "Processor.cpp"
#include "Store.cpp"

using namespace std;


/**
* 
*/
Store loadFile(Store theStore){

	string fileName;
	cout << "Enter Filename (Without Extension): " << endl;
	cin >> fileName;
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
		cin >> option;

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
