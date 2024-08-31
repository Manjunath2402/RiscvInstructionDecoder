#include <iostream>
#include <string>
#include <algorithm>
#include <unordered_map>
#include <map>
using namespace std;

string decoder(string, int);
string Rdecoder(string, string, string, string);
string Idecoder(string, string, string, string);
string Sdecoder(string, string, string, string);
string Bdecoder(string, string, string, string);
string Udecoder(string, string, string);
string Jdecoder(string, string, string);

string binaryToHex(string);
string hexToBinary(string);
string DecToBin(string);

string RegisterNumber(string);  // Returns register number in binary format.
void LoadInstructionData();

struct Rformat{
    string operation;
    string opcode;
    string funct3;
    string funct7;
    Rformat(){
        operation = "";
        opcode = "";
        funct3 = "";
        funct7 = "";
    }
    Rformat(string s1, string s2, string s3, string s4){
        operation = s1;
        opcode = s2;
        funct3 = s3;
        funct7 = s4;
    }
    Rformat operator= (Rformat r){
        operation = r.operation;
        opcode = r.opcode;
        funct3 = r.funct3;
        funct7 = r.funct7;
        return *this;
    }
};

struct Iformat{
    string operation;
    string opcode;
    string funct3;
    Iformat() : operation(""), opcode(""), funct3("") {}

    Iformat(string s1, string s2, string s3){
        operation = s1;
        opcode = s2;
        funct3 = s3;
    }
    Iformat operator= (Iformat i){
        operation = i.operation;
        opcode = i.opcode;
        funct3 = i.funct3;
        return *this;
    }
};

struct Sformat{
    string operation;
    string opcode;
    string funct3;
    Sformat() : operation(""), opcode(""), funct3("") {}

    Sformat(string s1, string s2, string s3){
        operation = s1;
        opcode = s2;
        funct3 = s3;
    }
    Sformat operator= (Sformat s){
        operation = s.operation;
        opcode = s.opcode;
        funct3 = s.funct3;
        return *this;
    }
};

class Bformat{
    public:
    string operation;
    string opcode;
    string funct3;
    Bformat(): operation(""), opcode(""), funct3("") {}
    Bformat(string s1, string s2, string s3){
        operation = s1;
        opcode = s2;
        funct3 = s3;
    }
    Bformat operator=(Bformat ins){
        operation = ins.operation;
        opcode = ins.opcode;
        funct3 = ins.funct3;
        return *this;
    }
};

class Uformat{
    public:
    string operation;
    string opcode;
    Uformat(): operation(""), opcode("") {}
    Uformat(string s1, string s2){
        operation = s1;
        opcode = s2;
    }
    Uformat operator=(Uformat ins){
        operation = ins.operation;
        opcode = ins.opcode;
        return *this;
    }
};

class Jformat{
    public:
    string operation;
    string opcode;
    Jformat(): operation(""), opcode("") {}
    Jformat(string s1, string s2){
        operation = s1;
        opcode = s2;
    }
    Jformat operator=(Jformat ins){
        operation = ins.operation;
        opcode = ins.opcode;
        return *this;
    }
};