/**
*Class which holds the nessessary data structures and logic to simulate the Manchester Baby's processor.
*
*Authors : Rory Magowan, Daniel Bereton, Daniel Kinnaird
*Version : 1.0 22nd November 2015
*
*/

class Processor{

	private : 

		//Boolean Array for the Accumulator
		bool accumulator[32];
		//Boolean Array for the CI (Control Instruction)
		bool ci[32];
		//Boolean Array for the PI (Present Instruction)
		bool pi[32];

	public : 	

		Processor();
		void setAccumulator(bool accumulator[32]);
		bool* getAccumulator();
		void setCI(bool memoryAddress[32]);
		bool* getCI();
		void setPI(bool instruction[32]);
		bool* getPI();
		void resetCI();
		void resetAccumulator();
		int convertBinToDec(bool binary[], int length);
		bool* convertDecToBin(int decimal);
		bool* negate(bool operand[32]);
		void increment();
		int getOp(int start, int end);

};
