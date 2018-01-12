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
		std::cout << programCounter << " : (" << programMemory[programCounter] << ") ";

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
			case WRITE: std::cout << "WRITE thing in " 	<< addr << " to CONSOLE" 	<< std::endl;
						std::cout << ram[addr] << std::endl;
				break;
			case LOAD: 	std::cout << "LOAD thing in " 	<< addr << " into Acc "		<< std::endl;
						accumulator = ram[addr];
				break;
			case STORE: std::cout << "STORE Acc into " 	<< addr 					<< std::endl;
						ram[addr] = accumulator;
				break;
			case MUL: 	std::cout << "MUL by thing in " << addr 					<< std::endl;
						accumulator *= ram[addr];
				break;
			case DIV: 	std::cout << "DIV by thing in " << addr 					<< std::endl;
						accumulator /= ram[addr];
				break;
			case ADD: 	std::cout << "ADD thing in " 	<< addr 					<< std::endl;
						accumulator += ram[addr];
				break;
			case SUB: 	std::cout << "SUB thing in " 	<< addr 					<< std::endl;
						accumulator -= ram[addr];
				break;
			case BRANCH:std::cout << "BRANCH to " 		<< addr 					<< std::endl;
						programCounter = addr;
				break;
			case BRANCH_IFNEG:
						std::cout << "BRANCH IFNEG to " << addr 					<< std::endl;
						programCounter = accumulator < 0 ? addr : programCounter ;
				break;
			case BRANCH_IFZERO:
						std::cout << "BRANCH IFZERO to " << addr 					<< std::endl;
						programCounter = accumulator == 0 ? addr : programCounter;
				break;
			case HALT: 	std::cout << "HALT" 										<< std::endl; break;

			default:
						std::cout << op << " was an invalid opcode" 				<< std::endl; break;
		}

	}while( !instructionIsHalt(inst) );

}

/*!
 * @brief Constructor
 */
Simpletron::Simpletron( void )
: programCounter( 0 )
{
	programMemory.fill(0);
	ram.fill(0);
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

}


