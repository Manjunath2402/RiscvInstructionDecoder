#include <iostream>
#include <fstream>
#include <string>
#include "prototypes.hh"
using namespace std;

int main(){
    LoadInstructionData();
    /*ifstream file;
    ofstream ofile;
    file.open("input.s", ios::in);
    ofile.open("output.hex", ios::out);
    string s;
    while (true){   
        if(file.eof()) break;
        getline(file, s);
        ofile << decoder(s);
    }
    file.close();
    ofile.close();
    */
    string s = Idecoder("ld", "x5", "x6", "-33");
    cout << s << endl;

    return 0;
}
