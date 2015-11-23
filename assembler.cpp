#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <bitset>
#include <algorithm>

using namespace std;

string instructionSet[7][2];
//vector<string> instructionSet[8][2];
struct symbol
{
    string name;
    string data;
    string line;
};
vector<symbol> symbolTable;
vector<string> program;

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
string binaryConv(int n)
{
    string str="";
    int binary;
    bitset<32> x(n);
    if(n<0)
    {
        n=n-(n+n);
        bitset<32> y(n);
        y.flip();
        bitset<32> z(y.to_ulong() + 1);
        str=z.to_string();
        x=z;
    }
    str=x.to_string();
    reverse(str.begin(),str.end());
    return str;
}

void openInstSet()
{
    string lines[7];
    string line="";
    ifstream file ("instructionSet.txt");
    if (file.is_open())
    {
        for(int i=0; i<7; i++)
        {
            getline (file,line);
            lines[i]=line;
        }
        file.close();
    }
    for(int j=0; j<7; j++)
    {
        stringstream split(lines[j]);
        for (int k=0; k<2; k++)
        {
            getline(split, instructionSet[j][k],' ');
        }
    }
}

void openProgram()
{
    ifstream file ("BabyTest1-Assembler.txt");
    string line="";
    if (file.is_open())
    {
        while(getline (file,line))
        {
            for (int j=0; j<line.size(); j++)
            {
                if(line.at(j)==';')
                {
                    line.erase(j,(line.size()-j));
                }
            }
            if(!line.empty())
                program.push_back(line);
        }
        file.close();
    }
}

//POPULATE SYMBOL TABLE
void loadSymbols()
{
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

            }
        }
    }

}

void convProgram()
{
    string op="";
    string operand="";
    string newLine="00000000000000000000000000000000";

    for (int i=0; i<program.size(); i++)
    {
        newLine="00000000000000000000000000000000";
        for (int k=0; k<7; k++)
            if (program.at(i).find(instructionSet[k][1])!=std::string::npos)
            {
                op=instructionSet[k][0];
                newLine.at(13)=op.at(0);
                newLine.at(14)=op.at(1);
                newLine.at(15)=op.at(2);
            }
        for (int j=0; j<symbolTable.size(); j++)
            if (program.at(i).find(symbolTable.at(j).name)!=std::string::npos)
            {
                operand="";
                operand=symbolTable.at(j).line;
                int n=0;
                istringstream (operand) >> n;
                operand=binaryConv(n);
                newLine.at(0)=operand.at(0);
                newLine.at(1)=operand.at(1);
                newLine.at(2)=operand.at(2);
                newLine.at(3)=operand.at(3);
                newLine.at(4)=operand.at(4);
            }
        program.at(i)=newLine;
    }

    for (int i=0; i<symbolTable.size(); i++)
    {
        if (symbolTable.at(i).data.at(0)=='V'&&symbolTable.at(i).data.at(1)=='A'&&symbolTable.at(i).data.at(2)=='R')

        {
            int n;
            string str=symbolTable.at(i).data;
            str.erase(0,3);
            istringstream (str) >> n;
            int line;
            istringstream (symbolTable.at(i).line) >> line;
            program.at(line)=binaryConv(n);
        }
    }
}

void outToFile()
{

    ofstream file ("machineCode.txt");
    if (file.is_open())
    {
        for (int i; i<program.size(); i++)
        {
            file<<program.at(i)<<endl;
        }
        file.close();
    }



}

int main()
{
    openInstSet();
    openProgram();
    loadSymbols();
    convProgram();
    outToFile();

    for (int i; i<program.size(); i++)
    {
        cout<<program.at(i)<<endl;
    }
    return 0;
}
