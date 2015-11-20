class Processor{

	private : 

		bool accumulator[32];
		bool ci[32];
		bool pi[32];

	public : 	

		Processor();
		void resetCI();
		int convertBinToDec(bool binary[], int length);
		bool* convertDecToBin(int decimal);
		void increment();
		int fetchOperand();

};
