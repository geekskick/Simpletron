//
// Created by Patrick Mintram on 12/04/2017.
//

#ifndef SIMPLETRON_SIMPLETRON_H
#define SIMPLETRON_SIMPLETRON_H


#include <cstdint>
#include <array>


class Simpletron
{
public:

	/*!
	 * @enum OpCode The different OpCodes possible
	 */
	enum OpCode { 	READ = 10,
					WRITE = 11,
					LOAD = 20,
					STORE = 21,
					ADD = 30,
					SUB = 31,
					MUL = 32,
					DIV = 33,
					BRANCH = 40,
					BRANCH_IFNEG = 41,
					BRANCH_IFZERO = 42,
					HALT = 43
	};
	Simpletron( void );
	~Simpletron( void ) {}
	void loadProgramIntoMemory( int *program );
	void disassembleProgram( void );
	void dump(void);

private:
	static constexpr int PROG_MEM_SIZE 		= 100;
	static constexpr int RAM_SIZE			= 100;
	std::array<uint32_t, PROG_MEM_SIZE> programMemory;
	std::array<int32_t, RAM_SIZE> ram;
	int32_t accumulator;
	int programCounter;

	bool instructionIsHalt( uint32_t instruction );
	int getOpcodeFromInstruction( uint32_t instruction );
	int getAddressFromInstruction( uint32_t instruction );




};


#endif //SIMPLETRON_SIMPLETRON_H
