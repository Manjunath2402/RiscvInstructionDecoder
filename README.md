# Risc-V Instruction Decoder

### Goal of the project:
To convert given set of RISC V instructions into their machine code equivalent. The machine code is outputed in Hexadecimal format for human readability.

### Input format:
Write the set of Instructions to be converted in a file named ***input.s***. The instructions in the input file should be written as follows:
1) If there is a label to a instruction provide a space after the colon.
2) Provide a space after writing operation.
3) Provide a space after writing register numbers.
Example instruction: Label1: *addi x1, x2, 20.*

The register names can be written as their aliases. The decoder can handle instructions with mixture of register numbers and aliases.
Example the above can be written like this *addi ra, sp, 20.* or *addi ra, x2, 20* or *addi x1, sp, 20*.

### Output:
The assembly code equivalent machine code in hexadecimal format will be outputed in ***output.hex*** file. If the file is not present, The decoder will
create the file. If the file is already present then the output data will overwrite the previous data in it.
