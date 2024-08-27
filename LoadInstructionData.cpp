#include "prototypes.hh"

map<string, string> BinToHex = {
    {"0000", "0"}, {"0001", "1"}, {"0010", "2"}, {"0011", "3"},
    {"0100", "4"}, {"0101", "5"}, {"0110", "6"}, {"0111", "7"},
    {"1000", "8"}, {"1001", "9"}, {"1010", "A"}, {"1011", "B"},
    {"1100", "C"}, {"1101", "D"}, {"1110", "E"}, {"1111", "F"}
};

map<string, string> Registers = {
    {"x0", "00000"}, {"x1", "00001"}, {"x2", "00010"}, {"x3", "00011"}, {"x4", "00100"}, {"x5", "00101"},
    {"x6", "00110"}, {"x7", "00111"}, {"x8", "01000"}, {"x9", "01001"}, {"x10", "01010"}, {"x11", "01011"},
    {"x12", "01100"}, {"x13", "01101"}, {"x14", "01110"}, {"x15", "01111"}, {"x16", "10000"}, {"x17", "10001"},
    {"x18", "10010"}, {"x19", "10011"}, {"x20", "10100"}, {"x21", "10101"}, {"x22", "10110"}, {"x23", "10111"},
    {"x24", "11000"}, {"x25", "11001"}, {"x26", "11010"}, {"x27", "11011"}, {"x28", "11100"}, {"x29", "11101"},
    {"x30", "11110"}, {"x31", "11111"},
    // aliases
    {"zero", "00000"}, {"ra", "00001"}, {"sp", "00010"}, {"gp", "00011"}, {"tp", "00100"}, {"t0", "00101"},
    {"t1", "00110"}, {"t2", "00111"}, {"s0", "01000"}, {"s1", "01001"}, {"a0", "01010"}, {"a1", "01011"},
    {"a2", "01100"}, {"a3", "01101"}, {"a4", "01110"}, {"a5", "01111"}, {"a6", "10000"}, {"a7", "10001"},
    {"s2", "10010"}, {"s3", "10011"}, {"s4", "10100"}, {"s5", "10101"}, {"s6", "10110"}, {"s7", "10111"},
    {"s8", "11000"}, {"s9", "11001"}, {"s10", "11010"}, {"s11", "11011"}, {"t3", "11100"}, {"t4", "11101"},
    {"t5", "11110"}, {"t6", "11111"},
    // fp special case
    {"fp", "01000"}
};

// Iformat addi{"addi", "0010011", "000"};
// Iformat xori{"xori", "0010011", "100"};
// Iformat ori{"ori", "0010011", "110"};
// Iformat andi{"andi", "0010011", "111"};
// Iformat slti{"slti", "0010011", "010"};
// Iformat sltiu{"sltiu", "0010011", "011"};

unordered_map<string, Rformat> mapR;
unordered_map<string, Iformat> mapI;
void LoadInstructionData(){
    mapR["add"] = Rformat("add", "0110011", "000", "0000000");
    mapR["sub"] = Rformat("sub", "0110011", "000", "0100000");
    mapR["xor"] = Rformat("xor", "0110011", "100", "0000000");
    mapR["or"] = Rformat ("or", "0110011", "110", "0000000");
    mapR["and"] = Rformat("and", "0110011", "111", "0000000");
    mapR["sll"] = Rformat ("sll", "0110011", "001", "0000000");
    mapR["srl"] = Rformat ("srl", "0110011", "101", "0000000");
    mapR["sra"] = Rformat ("srl", "0110011", "101", "0100000");
    mapR["slt"] = Rformat ("srl", "0110011", "010", "0000000"); //extra
    mapR["sltu"] = Rformat ("srl", "0110011", "011", "0000000"); //extra

    mapI["addi"] = Iformat( "addi", "0010011", "000");
    mapI["xori"] = Iformat( "xori", "0010011", "100");
    mapI["ori"] = Iformat( "ori", "0010011", "110");
    mapI["andi"] = Iformat( "andi", "0010011", "111");
    mapI["slli"] = Iformat( "slli", "0010011", "001");
    mapI["srli"] = Iformat( "srli", "0010011", "101"); // is operation really necessary in the class
    mapI["srai"] = Iformat( "srai", "0010011", "101");
    mapI["lb"] = Iformat( "lb", "0000011", "000");
    mapI["lh"] = Iformat( "lh", "0000011", "001");
    mapI["lw"] = Iformat( "lw", "0000011", "010");
    mapI["ld"] = Iformat( "ld", "0000011", "011");
    mapI["lbu"] = Iformat( "lbu", "0000011", "100");
    mapI["lhu"] = Iformat( "lhu", "0000011", "101");
    mapI["lwu"] = Iformat( "lwu", "0000011", "110");
    mapI["jalr"] = Iformat( "jalr", "1100111", "000");
// slti, sltiu

}

string decoder(string s){
    string machine_code;
    char c = s[0];
    string temp[5];
    int i = 0;
    int j = 0;
    while (c != '\0'){
        if(c == ' ' || c == '('){
            i++;
        }
        else if(c != ','){
            temp[i] += c;
        }
        j++;
        c = s[j];  // need to error handle if imediate value is too large
    }
    if(mapR.find(temp[0]) != mapR.cend()){
        machine_code = Rdecoder(temp[0], temp[1], temp[2], temp[3]);
    }
    else if(mapI.find(temp[0]) != mapI.end()){
        machine_code = Idecoder(temp[0], temp[1], temp[2], temp[3]);
    }
    return machine_code;
}

string Rdecoder(string Op, string rd, string rs1, string rs2){
    rd = RegisterNumber(rd);
    rs1 = RegisterNumber(rs1);
    rs2 = RegisterNumber(rs2);
    string s = "";
    // funct7, rs2, rs1, funct3, rd, opcode
    s += (mapR[Op]).funct7;
    s += rs2;
    s += rs1;
    s += (mapR[Op]).funct3;
    s += rd;
    s += (mapR[Op]).opcode;
    return binaryToHex(s);
}

string Idecoder(string Op, string rd, string rs1, string immediate){
    rd = RegisterNumber(rd);
    rs1 = RegisterNumber(rs1);
    string s = "";
    immediate = DecToBin(immediate);
    immediate = immediate.substr(0,12);
    reverse(immediate.begin(), immediate.end());
    // immediate, rs1, funct3, rd, opcode
    s += immediate;
    s += rs1;
    s += (mapI[Op]).funct3;
    s += rd;
    s += (mapI[Op]).opcode;
    return binaryToHex(s);
}


string binaryToHex(string s){
    string fourBin;
    string converted = "";
    for (size_t i = 0; i < 29; i = i + 4){
        fourBin = "";
        fourBin += s[i];
        fourBin += s[i + 1];
        fourBin += s[i + 2];
        fourBin += s[i + 3];
        converted += BinToHex[fourBin];
    }
    return converted;
}

string DecToBin(string s){
    string bin = "";
    int dec = 0;
    for(int i = 0; i<s.size(); i++){
        dec = dec*10 + int(bin[i] - '0'); 
    }
    if(dec > 2047 || dec < -2048){
        cout << "Immediate value " << dec << " does not fit in 12 bits" << endl;
        exit(0); //properly handle exit
    }
    while(dec != 0){
        if(dec%2==0){
            bin += "0";
        }
        else{
            bin += "1";
        }

        dec/=2;
    }
    return bin;

}

string RegisterNumber(string r){
    return Registers[r];
}