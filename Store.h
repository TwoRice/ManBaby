class Store{

	private :

		bool memory[32][32];

	public : 

		Store();
		bool* readMemory(int location);
		void writeMemory(int location, bool data[32]);
		void loadProgram(string fileName);

};

