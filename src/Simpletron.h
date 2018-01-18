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
					WRITEA = 12,
					LOAD = 20,
					STORE = 21,
					PUSH = 22,
					LOADL = 50,
					LOADA = 51,
					POP = 23,
					CALL = 24,
					RET = 25,
					ADD = 30,
					SUB = 31,
					MUL = 32,
					DIV = 33,
					BRANCH = 40,
					BRANCH_IFNEG = 41,
					BRANCH_IFZERO = 42,
					HALT = 43,
					DUMP = 99
	};
	Simpletron( bool debug = false );
	~Simpletron( void ) {}
	void loadProgramIntoMemory( int *program );
	void disassembleProgram( void );
	void dump(void);

private:
	static constexpr int PROG_MEM_SIZE 		= 100;
	static constexpr int RAM_SIZE			= 100;
	static constexpr int STACK_POINTER_LOC 	= RAM_SIZE - 1;
	const bool debug;
	std::array<uint32_t, PROG_MEM_SIZE> programMemory;
	std::array<int32_t, RAM_SIZE> ram;
	int32_t accumulator;
	int programCounter;

	bool instructionIsHalt( uint32_t instruction );
	int getOpcodeFromInstruction( uint32_t instruction );
	int getAddressFromInstruction( uint32_t instruction );




};


#endif //SIMPLETRON_SIMPLETRON_H
