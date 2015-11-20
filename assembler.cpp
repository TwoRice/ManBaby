#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

using namespace std;

string instructionSet[8][2];
//vector<string> instructionSet[8][2];
vector<string> program;

void openInstSet()
{
    string lines[8];
    string line="";
    ifstream file ("instructionSet.txt");
    if (file.is_open())
    {
        for(int i=0; i<8; i++)
        {
            getline (file,line);
            lines[i]=line;
        }
        file.close();
    }
    for(int j=0; j<8; j++)
    {
        stringstream split(lines[j]);
        for (int k=0; k<2; k++)
        {
            getline(split, instructionSet[j][k],' ');
        }
    }
}

void loadProgram()
{
    ifstream file ("BabyTest1-Assembler.txt");
    string line="";
    if (file.is_open())
    {
        while(getline (file,line))
        {
            program.push_back(line);
        }
        file.close();
    }

    //REMOVE COMMERNTS
    for (int i=0; i<program.size(); i++)
    {
        for (int j=0; j<program.at(i).size();j++)
        {
            if(program.at(i).at(j)==';')
            {
                program.at(i).erase(j,(program.at(i).size())-j);
            }
        }
        cout << program.at(i) << endl;
    }


}

int main()
{
    openInstSet();
    loadProgram();

    return 0;
}
