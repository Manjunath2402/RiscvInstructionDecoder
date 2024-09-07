#include <iostream>
#include <fstream>
#include <string>
#include "prototypes.hh"
using namespace std;

unordered_map<string, int> LabelData;

int main(){
    LoadInstructionData();

    ifstream file;
    ofstream ofile;

    file.open("input.s", ios::in);
    ofile.open("output.hex", ios::out);

    string s;
    int curren_line_no = 0;

    while (true){
        if(file.eof()) break;

        getline(file, s);
        curren_line_no++;

        char iterator = s[0];
        int index = 0;
        string label = "";
        string temp = "";

        while (iterator != '\0'){
            if(iterator == ':'){
                label = temp;
                break;
            }
            temp += iterator;
            index++;
            iterator = s[index];
        }

        // if there is no colon in the instruction then label will never be assigned.
        if(label != ""){
            if(LabelData[label] == 0){
                LabelData[label] = curren_line_no;
            }
            else{
                cout << "Same Label for two different instructions, Label: " << label << endl;
                cout << "1st instance Line number: " << LabelData[label] << endl;
                cout << "2nd instance Line number: " << curren_line_no << endl;
                exit(0);
            }
        }
    }

    // we will put input file buffer to start of the file.
    file.clear();
    file.seekg(0);
    curren_line_no = 0; // came to the start of the file again.
    
    while (true){   
        if(file.eof()) break;

        getline(file, s);
        curren_line_no++;

        ofile << decoder(s, curren_line_no) << endl;
    }
    
    file.close();
    ofile.close();

    return 0;
}
