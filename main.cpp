#include <iostream>
#include "Simpletron.h"

int program[] = { 1000, 1001, 2001, 3000, 2103, 1103, // simple addition and show result
				  1010, 2010, 3110, 4212, 0000, 0000, // subtract should == 0 and branch to next bit
				  1020, 1021, 2020, 3121, 4118, 0000, // if the user enters a larger number second skip to halt, otherwise 'invalid' will display
				  4300 };
int main( )
{
	std::cout << "Simpletron Disassembler in action!" << std::endl;
	Simpletron s;
	s.loadProgramIntoMemory(program);
	s.disassembleProgram();
	return 0;
}