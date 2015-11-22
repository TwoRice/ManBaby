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
    //if (n=0){
    //    str="00000000000000000000000000000000";
    //}else{
        int binary;
        bitset<32> x(n);
        x.flip();
        x.flip(x.size()-1);
        stringstream ss;
        ss << x;
        str = ss.str();
        reverse(str.begin(),str.end());
    //}
    return str;
}
string binaryConvOperand(int n){
    string str="";
    //if (n=0){
    //    str="00000000000000000000000000000000";
    //}else{
        int binary;
        bitset<32> x(n);
        stringstream ss;
        ss << x;
        str = ss.str();
        reverse(str.begin(),str.end());
    //}
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
            program.push_back(line);
        }
        file.close();
    }

    //REMOVE COMMERNTS + WHITESPACE
    for (int i=0; i<program.size(); i++)
    {
        for (int j=0; j<program.at(i).size(); j++)
        {
            if(program.at(i).at(j)==';')
            {
                program.at(i).erase(j,(program.at(i).size()-j));
            }
            //trim(program.at(i));
            //removeSpace(program.at(i));
        }
        cout<<program.at(i)<<endl;
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

            }
        }
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

void convProgram()
{
    string op="";
    string operand="";
    string newLine="00000000000000000000000000000000";

    for (int i=0; i<program.size(); i++)
    {
        newLine="00000000000000000000000000000000";
        for (int k=0; k<7; k++)
        if (program.at(i).find(instructionSet[k][1])!=std::string::npos){
            op=instructionSet[k][0];
            newLine.at(13)=op.at(0);
            newLine.at(14)=op.at(1);
            newLine.at(15)=op.at(2);
        }
        for (int j=0; j<symbolTable.size(); j++)
        if (program.at(i).find(symbolTable.at(j).name)!=std::string::npos){
                operand="";
                operand=symbolTable.at(j).line;
                int n=0;
                istringstream (operand) >> n;
                //NEXT LINE NOT NEEDED WHEN EMPTY ELEMENTS ARE REMOVED FROM VECTOR
                n=n-4;
                operand=binaryConvOperand(n);
                newLine.at(0)=operand.at(0);
                newLine.at(1)=operand.at(1);
                newLine.at(2)=operand.at(2);
                newLine.at(3)=operand.at(3);
                newLine.at(4)=operand.at(4);
        }

        cout<<newLine<<endl;


//        for (int j; j<program.at(i).size(); j++)
//        {
//
//            if (program.at(i).at(j)==':')
//            {
//                stringstream split(program.at(i));
//                getline(split, op,':');
//                for (int j; j<symbolTable.size(); j++)
//                {
//
//                    if(op==symbolTable.at(j).name)
//                    {
//
//                    }
//                }
//            }
//        }
    }
}

int main()
{
    openInstSet();
    openProgram();
    loadSymbols();
//    for (int i; i<program.size(); i++)
//    {
//        cout<<program.at(i)<<endl;
//    }
    convProgram();
    return 0;
}
