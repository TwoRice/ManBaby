/**
*Class which holds the nessessary data structures and logic to simulate the Manchester Baby's Store.
*(memory)
*
*Authors : Rory Magowan, Daniel Bereton, Daniel Kinnaird
*Version : 1.0 22nd November 2015
*
*/

class Store{

	private :

		//2D boolean array for the memory
		bool memory[32][32];

	public : 

		Store();
		bool* readMemory(int location);
		void writeMemory(int location, bool data[32]);
		bool loadProgram(string fileName);

};
