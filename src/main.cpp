#include <iostream>
#include "Simpletron.h"

int program[] = { 1000, 1001, 2001, 3000, 2103, 1103, // simple addition and show result
				  1010, 2010, 3110, 4212, 0000, 0000, // subtract should == 0 and branch to next bit
				  1020, 1021, 2020, 3121, 4118, 0000, // if the user enters a larger number second skip to halt, otherwise 'invalid' will display
				  4300 };

int stackTest[] = { 
	5001, // 01 into acc
	2200, // push
	5002, // 02 into stack
	2200, // push
	9900, // dump
	2300, // pop into acc
	2100, // store acc into 00
	2300, // pop
	2101, // store acc into 01
	9900, // dump
	5099, // load acc with 99
	2100, // store in 00
	2300, // pop
	3100, // subtract 99
	4216, // if zero (passed) branch to halt
	4050, // branch to invalid location if failure
	4300  // halt
};

#define FN_ADDR 23
#define EXIT_ADDR 38
#define RET_ADDR 37
#define LOOP_ADDR 25
int printTest[] = {
	5004, 
	2100, // 04 in 00 (stringlength)
	5070, // F
	2101,
	5085, // U
	2102, 
	5067, // C
	2103,
	5075, // k
	2104,
	5000 + FN_ADDR, // add of function
	2400, // call it
	5003,
	2100, // 3 in 00
	5085, // U
	2103,
	5079, // O
	2102,
	5089, // Y
	2101, 
	5000 + FN_ADDR, // address of function
	2400, // call it 
	4000 + EXIT_ADDR, // exit
	//print from 1 using length in 0 (23 is next line)
	5001, // 1 in acc
	2111, // store in 11
	2200, // push
	5100, // load into acc the location current in acc
	1200, // printf
	2300, // pop
	2110, // store in 10
	2000, // load 4
	3110, // sub thing in 10
	4200 + RET_ADDR, // branch if zero to 37 (ret)
	2010, // reload thing in 10 (the loop index)
	3011, // add 1
	4000 + LOOP_ADDR, // branch to 25
	9900, // dump
	2500, // return
	4300
};

int callTest[] = {
	5010, // load literal 10 into acc
	9900, // dump memory
	2400, // call thing pointed to by acc
	4017, 0, 0, 0, 0, 0, 0,  // branch to 17 (halt)
	1000, 1001, 2001, 3000, 2103, 1103, 2500,  // simple addition and show result, then ret
	4300 // halt
};

int main(const int argc, const char **argv)
{
	bool debug = false;
	if(argc == 2 && std::string(argv[1]) == "debug"){ debug = true; }
	std::cout << "Simpletron Disassembler in action!" << std::endl;
	Simpletron s(debug);

	//s.loadProgramIntoMemory(callTest);
	//s.disassembleProgram();

	s.loadProgramIntoMemory(printTest);
	s.disassembleProgram();
	return 0;
}