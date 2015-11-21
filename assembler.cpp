#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

using namespace std;

string instructionSet[8][2];
//vector<string> instructionSet[8][2];
vector<string> program;
struct symbol{
    string name;
    string data;
    string line;
};

vector<symbol> symbolTable;

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
        for (int j=0; j<program.at(i).size(); j++)
        {
            if(program.at(i).at(j)==';')
            {
                program.at(i).erase(j,(program.at(i).size()-j));
            }
        }
    }


    //POPULATE SYMBOL TABLE
    string sLines[3]="";
    for (int i=0; i<program.size(); i++)
    {
        for (int j=0; j<program.at(i).size(); j++)
        {
            if(program.at(i).at(j)==':')
            {
                stringstream split(program.at(i));

                getline(split, sLines[0],':');
                stringstream ss;
                ss << i;
                string str = ss.str();
                sLines[1]=program.at(i);
                sLines[1].erase(0,j+1);
                sLines[2]=str;
                //symbol.push_back(sLines)

                //REMOVE WHITESPACE (DOESN'T FUCKING WORK BECAUSE COMPUTERS HATE ME)

                    for (int i=0; i<3; i++)
                    {
                        for (int j=0; j<sLines[i].size(); j++)
                        {
                            if(sLines[i].at(j)==' ')
                            {
                               sLines[i].erase(j,1);
                            }
                        }
                    }
                    //ADD SYMBOL TO TABLE WITH IT'S DATA AND LINE NUMBER
                    symbolTable.push_back(symbol());
                    symbolTable[symbolTable.size()-1].name=sLines[0];
                    symbolTable[symbolTable.size()-1].data=sLines[1];
                    symbolTable[symbolTable.size()-1].line=sLines[2];
                    cout << symbolTable[symbolTable.size()-1].name << endl;
                    cout << symbolTable[symbolTable.size()-1].data << endl;
                    cout << symbolTable[symbolTable.size()-1].line << endl;
            }
        }
    }
}




int main()
{
    openInstSet();
    loadProgram();

    return 0;
}
