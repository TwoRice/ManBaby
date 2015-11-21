#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

using namespace std;

string instructionSet[8][2];
//vector<string> instructionSet[8][2];
struct symbol
{
    string name;
    string data;
    string line;
};
vector<symbol> symbolTable;
vector<string> program;
vector<string> programOut;

void trim(string& s)
{
    size_t p = s.find_first_not_of(" \t");
    s.erase(0, p);

    p = s.find_last_not_of(" \t");
    if (string::npos != p)
        s.erase(p+1);
}

void removeSpace(string& s)
{

    for (int j=0; j<s.size(); j++)
    {
        if(s.at(j)==' ')
        {
            s.erase(j,1);
        }
    }

}
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

                //REMOVE WHITESPACE

                for (int i=0; i<3; i++)
                {
                    removeSpace(sLines[i]);
                    trim(sLines[i]);
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

//convProgram(){
//    for (int i; i<program.size();i++){
//        if (program.at(i)){
//
//        }
//    }
//}

int main()
{
    openInstSet();
    loadProgram();
//    convProgram();


    return 0;
}
