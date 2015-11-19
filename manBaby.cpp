#include <iostream>
#include <string>
#include "Processor.cpp"
#include "Store.cpp"

using namespace std;



/**
* 
*/
void loadFile(){

	string fileName;
	cout << "Enter Filename (Without Extension): " << endl;
	cin >> fileName;
	fileName.append(".txt");


}

/**
* 
*/
void displayMenu(){

	cout << "(1) Load Program" << endl;
	cout << "(2) Exit" << endl;
}

void Menu(){
	
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
			loadFile();

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

 	Menu();

	return 0;



}
