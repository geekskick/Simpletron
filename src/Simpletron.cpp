//
// Created by Patrick Mintram on 12/04/2017.
//

#include "Simpletron.h"
#include <string>
#include <cmath>
#include <iostream>

/*!
 * @brief Copies the contents of the program into the Simpletron's own memory.
 * Passing an array of any maximum size will tke up loads of memory, so instead passing the address of it is used
 * @param program The address of the instruction array to copy in. The final instruction should be HALT
 */
void Simpletron::loadProgramIntoMemory( int *program )
{
	int loadLocation = 0;

	/// If the program is just a HALT command dont bother copying
	if( getOpcodeFromInstruction( (uint32_t)program[loadLocation] )== (int)HALT ) { return; }

	programMemory.fill(0);
	ram.fill(0);
	ram[STACK_POINTER_LOC] = STACK_POINTER_LOC - 1;
	programCounter = 0;

	/// Assumes that the last instruction will be HALT
	do
	{
		programMemory[loadLocation] = (uint32_t)program[loadLocation];

	}
	while( !instructionIsHalt( program[loadLocation++] ) );

}

/*!
 * @brief Prints description of the program stored in memory to stdout
 */
void Simpletron::disassembleProgram( void )
{

	uint32_t inst;

	do
	{
		/// Print the location in the program memory
		//std::cout << programCounter << " : (" << programMemory[programCounter] << ") ";

		/// FETCH
		inst = programMemory[programCounter++];

		/// DECODE
		int addr = getAddressFromInstruction(inst);
		OpCode op = (OpCode)getOpcodeFromInstruction(inst);

		/// EXECUTE
		switch( op )
		{
			case READ: 	std::cout << "READ into " 		<< addr						<< std::endl << "> ";
						std::cin >> ram[addr];
				break;
			case WRITE: if(debug){ std::cout << "WRITE thing in " 	<< addr << " to CONSOLE" 	<< std::endl; }
						std::cout << ((char)ram[addr]); //<< std::endl;
				break;
			case WRITEA:if(debug){ std::cout << "WRITE thing in Acc to CONSOLE" 				<< std::endl;}
						std::cout << (char)accumulator;// << std::endl;
				break;
			case LOAD: 	if(debug){ std::cout << "LOAD thing in " 	<< addr << " into Acc "		<< std::endl;}
						accumulator = ram[addr];
				break;
			case LOADL: if(debug){ std::cout << "LOAD Literal  " 	<< addr << " into Acc "		<< std::endl;}
						accumulator = addr;
				break;
			case LOADA: if(debug){ std::cout << "LOAD thing in " << accumulator << " into Acc "	<< std::endl;}
						accumulator = ram[accumulator];
				break;
			case STORE: if(debug){ std::cout << "STORE Acc into " 	<< addr 					<< std::endl;}
						ram[addr] = accumulator;
				break;
			case MUL: 	if(debug){ std::cout << "MUL by thing in " << addr 					<< std::endl;}
						accumulator *= ram[addr];
				break;
			case DIV: 	if(debug){ std::cout << "DIV by thing in " << addr 					<< std::endl;}
						accumulator /= ram[addr];
				break;
			case ADD: 	if(debug){ std::cout << "ADD thing in " 	<< addr 					<< std::endl;}
						accumulator += ram[addr];
				break;
			case SUB: 	if(debug){ std::cout << "SUB thing in " 	<< addr 					<< std::endl;}
						accumulator -= ram[addr];
				break;
			case BRANCH:if(debug){ std::cout << "BRANCH to " 		<< addr 					<< std::endl;}
						programCounter = addr;
				break;
			case BRANCH_IFNEG:
						if(debug){ std::cout << "BRANCH IFNEG to " << addr 					<< std::endl;}
						programCounter = accumulator < 0 ? addr : programCounter ;
				break;
			case BRANCH_IFZERO:
						if(debug){ std::cout << "BRANCH IFZERO to " << addr 					<< std::endl;}
						programCounter = accumulator == 0 ? addr : programCounter;
				break;
			case HALT: 	std::cout << "HALT" 										<< std::endl; 
				break;
			case PUSH:	if(debug){ std::cout << "PUSH acc to stack " 							<< std::endl;}
						ram[ram[STACK_POINTER_LOC]--] = accumulator; 
				break;
			case POP:   if(debug){ std::cout << "POP from stack into acc" 						<< std::endl;}
						if(ram[STACK_POINTER_LOC] + 1 == STACK_POINTER_LOC) { break; }
						accumulator = ram[++ram[STACK_POINTER_LOC]];
				break;
			case CALL:  if(debug){ std::cout << "CALL subroutine at " << accumulator 			<< std::endl; }
						ram[ram[STACK_POINTER_LOC]--] = programCounter;
						programCounter = accumulator;
				break;
			case RET:	if(debug){ std::cout << "RETurn from subroutine to " << ram[ram[STACK_POINTER_LOC]+1] << std::endl;}
						programCounter = ram[++ram[STACK_POINTER_LOC]];
				break;
			case DUMP:	if(debug){ dump();}
				break;

			default:
						std::cout << op << " was an invalid opcode" 				<< std::endl; break;
		}

	}while( !instructionIsHalt(inst) );

}

/*!
 * @brief Constructor
 */

Simpletron::Simpletron( bool debug )
: programCounter( 0 ),
  debug(debug)
{
	programMemory.fill(0);
	ram.fill(0);
	ram[STACK_POINTER_LOC] = STACK_POINTER_LOC - 1;
}

/*!
 * @brief Test if the instruction in program memory is a HALT instruction
 * @param instruction The instruction to check if it's halt
 * @return true if HALT instruction is at that location
 */
bool Simpletron::instructionIsHalt( uint32_t instruction )
{
	return (OpCode)getOpcodeFromInstruction( instruction ) == HALT;
}

/*!
 * @brief Extract the opcode from the memory location as an int
 * @param instruction The instruction
 * @return The opcode as an int
 */
int Simpletron::getOpcodeFromInstruction( uint32_t instruction )
{
	// The opcode is stored as the upper two digit of a decimal number aka the number of hundreds
	return ( instruction / 100 );
}

/*!
 * @brief Extract the address from the memory location as an int
 * @param location The instruction
 * @return The address as an int
 */
int Simpletron::getAddressFromInstruction( uint32_t instruction )
{
	// The address is stored as the lower two digit of a decimal number aka the modulus
	return ( instruction % 100 );
}

/**
 * @brief      Dump the ram and progmem to stdout
 */
void Simpletron::dump(void)
{
	int i = 0;
	std::cout << "Register Dump:" << std::endl;
	for(auto const & r: ram)
	{
		std::cout << "\t" << std::dec << i++ <<":\t" << std::hex << r << std::endl;
	}

	i = 0;
	std::cout << "ProgMem Dump:" << std::dec << std::endl;
	for(auto const &p: programMemory)
	{
		std::cout << "\t" << i++ <<":\t" << p << std::endl;
	}
	std::cout << "Accumulator Dump:" << std::hex << std::endl;
	std::cout << "\t" << std::hex << accumulator << std::endl;
	std::cout << std::dec;

}


