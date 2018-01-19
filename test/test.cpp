#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "Simpletron.h"
#include <iostream>
#include <sstream>

struct cout_redirect {
	cout_redirect( std::streambuf * new_buffer )
			: old( std::cout.rdbuf( new_buffer ) )
	{ }

	~cout_redirect( ) {
		std::cout.rdbuf( old );
	}

private:
	std::streambuf * old;
};

TEST_CASE("ADD", "Add two numbers"){
	Simpletron s(true);
	std::stringstream redir;
	cout_redirect (redir.rdbuf());
	int program[] = { 5001, 2100, 5002, 2101, 2000, 3001, 2102, 2002, 1200, 4300 };

	s.loadProgramIntoMemory(program);
	s.disassembleProgram();
	REQUIRE(redir.str() == "3HALT");
}