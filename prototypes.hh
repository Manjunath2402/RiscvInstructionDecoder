#include <iostream>
#include <string>
#include <algorithm>
#include <unordered_map>
#include <map>
using namespace std;

string decoder(string);
string Rdecoder(string, string, string, string);
string Idecoder(string, string, string);
string binaryToHex(string);
string RegisterNumber(string);
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
    Iformat operator= (Iformat ins){
        operation = ins.operation;
        opcode = ins.opcode;
        funct3 = ins.funct3;
        return *this;
    }
};