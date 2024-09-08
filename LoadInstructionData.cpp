#include "prototypes.hh"

// Label Data defined in main file which conatain information about the label and their line number.
extern unordered_map<string, int> LabelData;

// Current line number for error handling only visible in this file.
static int current_line_no;

// Binary to Hex for fast access.
map<string, string> BinToHex = {
    {"0000", "0"}, {"0001", "1"}, {"0010", "2"}, {"0011", "3"},
    {"0100", "4"}, {"0101", "5"}, {"0110", "6"}, {"0111", "7"},
    {"1000", "8"}, {"1001", "9"}, {"1010", "A"}, {"1011", "B"},
    {"1100", "C"}, {"1101", "D"}, {"1110", "E"}, {"1111", "F"}
};

// Hex to Binary for fast access.
map<char, string> HexToBin = {
    {'0', "0000"}, {'1', "0001"}, {'2', "0010"}, {'3', "0011"},
    {'4', "0100"}, {'5', "0101"}, {'6', "0110"}, {'7', "0111"},
    {'8', "1000"}, {'9', "1001"}, {'A', "1010"}, {'B', "1011"},
    {'C', "1100"}, {'D', "1101"}, {'E', "1110"}, {'F', "1111"}
};

// Registers and their aliases with binary representation.
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

unordered_map<string, Rformat> mapR;
unordered_map<string, Iformat> mapI;
unordered_map<string, Sformat> mapS;
unordered_map<string, Bformat> mapB;
unordered_map<string, Uformat> mapU;
unordered_map<string, Jformat> mapJ;


// Will create instruction object upon calling. which will be done in the start of the main file.
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
    mapI["srli"] = Iformat( "srli", "0010011", "101");
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

    mapS["sd"] = Sformat("sd", "0100011", "011");
    mapS["sw"] = Sformat("sw", "0100011", "010");
    mapS["sh"] = Sformat("sh", "0100011", "001");
    mapS["sb"] = Sformat("sb", "0100011", "000");

    // Branch instructions.
    mapB["beq"] = Bformat("beq", "1100011", "000");
    mapB["bne"] = Bformat("bne", "1100011", "001");
    mapB["blt"] = Bformat("blt", "1100011", "100");
    mapB["bge"] = Bformat("bge", "1100011", "101");
    mapB["bltu"] = Bformat("bltu", "1100011", "110");
    mapB["bgeu"] = Bformat("bgeu", "1100011", "111");

    // Upper format instructions.
    mapU["lui"] = Uformat("lui", "0110111");
    mapU["auipc"] = Uformat("auipc", "0010111");

    // Jump format instruction.
    mapJ["jal"] = Jformat("jal", "1101111");
}


// The main decoder which will call specific instruction decoders.
string decoder(string s, int line_no){
    string machine_code; // The decode hexadecimal representation of the instruction.

    char iterator = s[0];
    string temp[5] = {"", "", "", "", ""}; // This will splits instruction, registers and immediates etc..

    int i = 0;
    int index = 0;
    current_line_no = line_no;

    while (iterator != '\0'){

        if(iterator == ':'){
            temp[i] = "";
            i = -1;
        }
        else if(iterator == ' ' || iterator == '('){
            i++;
        }
        else if(iterator != ',' && iterator != ')'){
            temp[i] += iterator;
        }

        index++;
        iterator = s[index];  // need to error handle if immediate value is too large
    }
    // In case of instructions which contains labels temp[3] will contain the label.


    if(mapR.find(temp[0]) != mapR.cend()){
        // If temp[4] is not equal to a empty string then there are more operands than 3.

        if(temp[4] != ""){
            cout << "Line number: " << line_no << ". ";
            cout << "More number of operands for the given instruction: " << temp[0] << ". " << endl;
            cout << "Instruction: " << s << ". " << "Valid for only 3 operands. " << endl;
            exit(0);
        }

        // In R format instruction there will always be three operands.
        // If there temp[3] is empty then there are less operands in the instruciton provided.

        if(temp[3] == ""){
            cout << "Line number: " << line_no << ". ";
            cout << "Few number of operands for the given instruction: " << temp[0] << ". " << endl;
            cout << "Instruction: " << s << ". " << endl;
            exit(0);
        }

        machine_code = Rdecoder(temp[0], temp[1], temp[2], temp[3]);
    }

    else if(mapI.find(temp[0]) != mapI.cend()){
        // In I format instructions the max number of operands are 3 so if temp[4] is not empty then more number of arguments are provided.

        if(temp[4] != ""){
            cout << "Line number: " << line_no << ". ";
            cout << "More number of operands for the given instruction: " << temp[0] << ". " << endl;
            cout << "Instruction: " << s << ". " << "Valid for only 3 operands. " << endl;
            exit(0);
        }
        
        // For load instructions the temp[3] will be operand2 and temp[2] will the offset.
        if(mapI[temp[0]].opcode == "0000011"){
            // If offset is not provided.
            if(temp[2] == ""){
                cout << "Immediate is not provided." << endl;
                cout << "Line number: " << current_line_no << endl;
                exit(0);
            }

            int offset = stoi(temp[2]);

            // If offset exceed the range that can be put in 12 bits.
            if(offset > 2047 || offset < -2048){
                cout << "Offset is out of range(-2048 to 2047)" << endl;
                cout << "Line number: " << line_no << endl;
                exit(0);
            }

            machine_code = Idecoder(temp[0], temp[1], temp[3], temp[2]);
        }
        // Instruction other than ld will come here.
        else{
            // If immediate is not provided.
            if(temp[3] == ""){
                cout << "Immediate is not provided." << endl;
                cout << "Line number: " << current_line_no << endl;
                exit(0);
            }

            int offset = stoi(temp[3]);

            // If offset exceed the range that can be put in 12 bits.
            if(offset > 2047 || offset < -2048){
                cout << "Offset " << offset<< " is out of range(-2048 to 2047). ";
                cout << "Line number: " << line_no << endl;
                exit(0);
            }

            machine_code = Idecoder(temp[0], temp[1], temp[2], temp[3]);
        }
    }

    else if(mapS.find(temp[0]) != mapS.cend()){

        // In S format instrution the number of operands are always 3.
        // If temp[4] is non empty then more number of operands are provided.
        if(temp[4] != ""){
            cout << "Line number: " << line_no << ". ";
            cout << "More number of operands for the given instruction: " << temp[0] << ". " << endl;
            cout << "Instruction: " << s << ". " << "Valid for only 3 operands. " << endl;
            exit(0);
        }

        // If offset is not provided.
        if(temp[2] == ""){
            cout << "Immediate is not provided." << endl;
            cout << "Line number: " << current_line_no << endl;
            exit(0);
        }

        int offset = stoi(temp[2]);

        // If offset is exceeding the range.
        if(offset > 2047 || offset < -2048){
            cout << "Exceeding immediate value, offset: " << offset << endl;
            cout << "Line number: " << line_no << endl;
            exit(0);
        }

        machine_code = Sdecoder(temp[0], temp[1], temp[3], temp[2]);
    }

    else if(mapB.find(temp[0]) != mapB.cend()){

        // If label is not found.
        int l = LabelData[temp[3]];
        if (l == 0) {
            cout << "Label Not Found, Label: " << temp[3] << endl;
            cout << "Line number: " << current_line_no << endl;
            exit(0);
        }

        int offset = (LabelData[temp[3]] - line_no) * 4;

        // If label exceeds the range. 
        if((offset > 4095) || (offset < -4096)){
            cout << "Exceeding branching capability, offset: " << offset << endl;
            cout << "Line number: " << line_no << endl;
            cout << "Try using 'jal' if this is an unconditinal branch" << endl;
            exit(0);
        }

        temp[3] = to_string(offset);  // temp[3] is in decimal.
        temp[3] = DecToBin(temp[3]);  // Converting label to decimal value.

        machine_code = Bdecoder(temp[0], temp[1], temp[2], temp[3]);
    }

    else if(mapU.find(temp[0]) != mapU.cend()){
        // If the instruction is a U format instruction then temp[1] will contain rd and temp[2] contain immediate.
        // Immediate value can be given as hexadecimal or decimal 
        // immediate value is shifted by 12 bits and then it is added to given value.
        // In case of auipc immediate is added to PC.
        if(temp[2] == ""){
            cout << "Immediate is not given." << endl;
            cout << "Line number: " << current_line_no << endl;
            exit(0);
        }

        // If the given immediate is a hexadecimal value.
        if(temp[2].substr(0,2) == "0x"){
            // value is in hexadecimal.
            temp[2] = hexToBinary(temp[2]);
        }

        else{
            temp[2] = DecToBin(temp[2]);
        }

        machine_code = Udecoder(temp[0], temp[1], temp[2]);
    }

    else if(mapJ.find(temp[0]) != mapJ.cend()){

        // If label is not found.
        int l = LabelData[temp[2]];
        if(l == 0){
            cout << "Label Not Found, Label: " << temp[2] << endl;
            cout << "Line number: " << current_line_no << endl;
            exit(0);
        }

        int offset = (LabelData[temp[2]] - line_no) * 4;
        temp[2] = to_string(offset);
        temp[2] = DecToBin(temp[2]);

        machine_code = Jdecoder(temp[0], temp[1], temp[2]);
    }

    else{
        // If instruction is not found.
        cout << "Invalid Instruction: " << temp[0] << ". " ;
        cout << "Line number: " << line_no << endl;
        exit(0);
    }

    return machine_code;
}

string Rdecoder(string Op, string rd, string rs1, string rs2){

    rd = RegisterNumber(rd);
    rs1 = RegisterNumber(rs1);
    rs2 = RegisterNumber(rs2);

    // If rd or rs1 or rs2 are empty meaning the given register is not defined. 
    if(rd == ""){
        cout << "Could not find the destination register." << endl;
        cout << "Line number: " << current_line_no << endl;
        exit(0);
    }
    if(rs1 == ""){
        cout << "Could not find the operand register 1." << endl;
        cout << "Line number: " << current_line_no << endl;
        exit(0);
    }
    if(rs2 == ""){
        cout << "Could not find the operand register 2." << endl;
        cout << "Line number: " << current_line_no << endl;
        exit(0);
    }

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

    // If rd or rs1 are empty meaning the given register is not defined.
    if(rd == ""){
        cout << "Could not find the destination register." << endl;
        cout << "Line number: " << current_line_no << endl;
        exit(0);
    }
    if(rs1 == ""){
        cout << "Could not find the operand register 1." << endl;
        cout << "Line number: " << current_line_no << endl;
        exit(0);
    }

    string s = "";

    immediate = DecToBin(immediate);
    reverse(immediate.begin(), immediate.end());
    immediate = immediate.substr(0,12);
    if(Op == "srai"){
        immediate = immediate.substr(0,6);
        immediate += "000010";
    }

    // immediate, rs1, funct3, rd, opcode
    reverse(immediate.begin(), immediate.end());
    s += immediate;
    s += rs1;
    s += (mapI[Op]).funct3;
    s += rd;
    s += (mapI[Op]).opcode;

    return binaryToHex(s);
}

string Sdecoder(string Op, string rs2, string rs1, string immediate){

    rs2 = RegisterNumber(rs2);
    rs1 = RegisterNumber(rs1);

    // If rs1 or rs2 are empty meaning the given register is not defined.
    if(rs1 == ""){
        cout << "Could not find the operand register 1." << endl;
        cout << "Line number: " << current_line_no << endl;
        exit(0);
    }
    if(rs2 == ""){
        cout << "Could not find the operand register 2." << endl;
        cout << "Line number: " << current_line_no << endl;
        exit(0);
    }

    string s = "";
    immediate = DecToBin(immediate);
    reverse(immediate.begin(), immediate.end());
    immediate = immediate.substr(0,12);
    // Sformat need only
    // immediate[11:5], rs2, rs1, funct3, imm[4:0], opcode
    reverse(immediate.begin(), immediate.end());

    s += immediate.substr(0,7);
    s += rs2;
    s += rs1;
    s += (mapS[Op]).funct3;
    s += immediate.substr(7,5);
    s += (mapS[Op]).opcode;

    return binaryToHex(s);
}

string Bdecoder(string Op, string rs1, string rs2, string offset){

    rs1 = RegisterNumber(rs1);
    rs2 = RegisterNumber(rs2);

    // If rs1 or rs2 are empty meaning the given register is not defined.
    if(rs1 == ""){
        cout << "Could not find the operand register 1." << endl;
        cout << "Line number: " << current_line_no << endl;
        exit(0);
    }
    if(rs2 == ""){
        cout << "Could not find the operand register 2." << endl;
        cout << "Line number: " << current_line_no << endl;
        exit(0);
    }

    reverse(offset.begin(), offset.end());
    offset = offset.substr(1, 12);
    // In B type instruction we don't care about the least significant byte as it will 
    // be zero.
    reverse(offset.begin(), offset.end());

    string s = "";
    s += offset[0]; // imm[12] - 1
    s += offset.substr(2, 6); // This captures imm[10:5] - 6
    s += rs2;
    s += rs1;
    s += (mapB[Op]).funct3;
    s += offset.substr(8, 4); // imm[4:1]
    s += offset[1]; // imm[11]
    s += (mapB[Op]).opcode;

    return binaryToHex(s);
}

string Udecoder(string Op, string rd, string imm){

    // passed imm is in binary.
    rd = RegisterNumber(rd);
    
    // If rd is empty then given register is not defined.
    if(rd == ""){
        cout << "Could not find the destination register." << endl;
        cout << "Line number: " << current_line_no << endl;
        exit(0);
    }

    imm += "000000000000";
    // adding 12 bits to the lsb.
    // we will ignore lsb 12 bits of imm.
    reverse(imm.begin(), imm.end());
    imm = imm.substr(12, 20);
    if(imm.length() < 20){
        int diff = (20 - imm.length());
        for (size_t i = 0; i < diff; i++){
            imm += "0";
        }
    }
    // Immediate now contain 20 bits.
    reverse(imm.begin(), imm.end());

    string s = "";
    s += imm;
    s += rd;
    s += (mapU[Op].opcode);

    return binaryToHex(s);
}

string Jdecoder(string Op, string rd, string imm){
    // we need 21 bits of imm and we will ignore 0th bit.

    rd = RegisterNumber(rd);
    
    // If rd is empty then given register is not defined.
    if(rd == ""){
        cout << "Could not find the destination register." << endl;
        cout << "Line number: " << current_line_no << endl;
        exit(0);
    }

    reverse(imm.begin(), imm.end());
    imm = imm.substr(1, 20);
    if(imm.length() < 20){
        int diff = 20 - imm.length();
        for (size_t i = 0; i < diff; i++){
            imm += "0";
        }
    }
    reverse(imm.begin(), imm.end());

    string s = "";
    s += imm[0]; // 1 bit.
    s += imm.substr(10, 10); // 12 bits.
    s += imm[9]; // 1 bit
    s += imm.substr(1, 8); // 8 bits
    s += rd;
    s += (mapJ[Op]).opcode;

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

string hexToBinary(string s){

    s = s.substr(2, (s.length() - 2));
    string bin = "";
    int index = 0;
    while (s[index] != '\0'){
        bin += HexToBin[s[index]];
        index++;
    }

    return bin;
}

string DecToBin(string s){

    string bin = "";
    int dec = 0;
    int i = 0;
    int check = -1;

    if(s[i] == '-'){
        i = 1;
    }
    for(; i<s.length(); i++){
        dec = dec*10 + int(s[i] - '0'); 
    }
    if(s[0] == '-'){
        dec = -dec;
        check = 0;
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
    while (bin.size() < 21)
    {
        bin += '0';
    }
    
    if(check == 0){
        for(int j = 0; j<bin.size(); j++){    
            if (bin[j] == '0' && check == 0){
                bin[j] = '0';
            }
            else if(bin[j] == '1' && check == 0){
                bin[j] = '1';
                check = 1;
            } 
            else if(bin[j] == '1' && check == 1){
                bin[j] = '0';
            }
            else if(bin[j] == '0' && check == 1){
                bin[j] = '1';
            }
        }
    }
    reverse(bin.begin(), bin.end());
    
    return bin;
}

string RegisterNumber(string r){
    return Registers[r];
}