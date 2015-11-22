class Processor{

	private : 

		bool accumulator[32];
		bool ci[32];
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
		int convertBinToDec(bool binary[], int length);
		bool* convertDecToBin(int decimal);
		bool* negate(bool operand[32]);
		void increment();
		int getOp(int start, int end);

};
