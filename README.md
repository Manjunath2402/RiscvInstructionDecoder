# Risc-V Instruction Decoder

### Purpose of the project:
To convert given set of RISC V instructions into their machine code equivalent. The machine code is outputed in Hexadecimal format for human readability.

### File system and running the program
The directory contains a header file ***prototypes.hh*** which contains classes of the instructions, prototypes of decoder functions for each instruction
format.

The ***LoadInstructionData.cpp*** contains the implementation of the decoders, maps which contain the register data, binary to hexa and hexadecimal maps.

The ***main.cpp*** file does all the I/O file handling, Label handling. This file contains the LabelData map which stores the Labels and their line numbers.

Running the program:
Simply run the make file. which will create the riscv_asm executable. Directly run this executable to get the output printed in the ***output.hex*** file.

### Input format:
Write the set of Instructions to be converted in a file named ***input.s***. The instructions in the input file should be written as follows:
1) The instruction operation name should always be written in smaller case alphabets. After writing the instruction operation always leave one empty space.
2) The register operands can be given with their numbers(i.e., x1, x2 etc.) or with their aliases. The decoder can handle both and mix of both normal number notation and their aliases.
3) After each operand put a comma and leave a empty space, unless the operand is the last one. 
4) If a instruction is labeled then the label should always be put in the start of the instruction and the label and the instruction should be separated by a colon and space. If the colon is not provided then it will be reported incorrect.

Example notations: *add x1, x3, x2*, *add ra, gp, sp*, *add x1, gp, x2* and *Label1: add x1, x2, x3*.
5) The load, store and *jalr* instructions can have their offset mentioned before the operand register. The register operand on which offset is present should be enclosed with paranthesis. 
6) The offset should only be given in decimal format.

Example notation: *ld x1, 0(x2)*, *sb x2, 80(x4)*, *jalr x0, 0(ra)*.
7) The branch instructions, jump and link instruction(*jal*) should only contain labels not any other offset value.
8) The *lui*, *auipc* instructions can handle both decimal and hexadecimal offsets.

### Output:
The assembly code equivalent machine code in hexadecimal format will be outputed in ***output.hex*** file. If the file is not present, The decoder will create the file. If the file is already present then the output data will overwrite the previous data in it.
