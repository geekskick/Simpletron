#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "Simpletron.h"
#include "redirection.h"


TEST_CASE("Add two numbers load and store and display on the screen"){
	Simpletron s;
	std::stringstream redir;
	cout_redirect pp(redir.rdbuf());

	int program[] = { 5001, 2100, 5002, 2101, 2000, 3001, 2102, 2002, 1200, 4300 };

	s.loadProgramIntoMemory(program);
	s.disassembleProgram();
	REQUIRE(redir.str() == "3HALT\n");
}

TEST_CASE("Stack Push Test"){
	Simpletron s;
	std::stringstream redir;
	cout_redirect pp(redir.rdbuf());

	int program[] = { 5001, 2200, 1198, 4300 };

	s.loadProgramIntoMemory(program);
	s.disassembleProgram();
	REQUIRE(redir.str() == "1HALT\n");
}

TEST_CASE("Stack Pop Test"){
	Simpletron s;
	std::stringstream redir;
	cout_redirect pp(redir.rdbuf());

	int program[] = { 5001, 2200, 5044, 2300, 1200, 4300 };

	s.loadProgramIntoMemory(program);
	s.disassembleProgram();
	REQUIRE(redir.str() == "1HALT\n");
}

TEST_CASE("Subtract a number and display on the screen"){
	Simpletron s;
	std::stringstream redir;
	cout_redirect pp(redir.rdbuf());

	int program[] = { 5010, 2100, 5002, 2101, 2000, 3101, 1200, 4300 };

	s.loadProgramIntoMemory(program);
	s.disassembleProgram();
	REQUIRE(redir.str() == "8HALT\n");
}

TEST_CASE("Multiply a number and display on the screen"){
	Simpletron s;
	std::stringstream redir;
	cout_redirect pp(redir.rdbuf());

	int program[] = { 5010, 2100, 5002, 2101, 2000, 3201, 1200, 4300 };

	s.loadProgramIntoMemory(program);
	s.disassembleProgram();
	REQUIRE(redir.str() == "20HALT\n");
}

TEST_CASE("Divide a number and display on the screen"){
	Simpletron s;
	std::stringstream redir;
	cout_redirect pp(redir.rdbuf());

	int program[] = { 5010, 2100, 5002, 2101, 2000, 3301, 1200, 4300 };

	s.loadProgramIntoMemory(program);
	s.disassembleProgram();
	REQUIRE(redir.str() == "5HALT\n");
}

TEST_CASE("Subract a number and branch if neg"){
	Simpletron s;
	std::stringstream redir;
	cout_redirect pp(redir.rdbuf());

	int program[] = { 5010, 2100, 5002, 2101, 3100, 4107, 0000, 5001, 1200, 4300 };

	s.loadProgramIntoMemory(program);
	s.disassembleProgram();
	REQUIRE(redir.str() == "1HALT\n");
}

TEST_CASE("Subract a number and branch if zero"){
	Simpletron s;
	std::stringstream redir;
	cout_redirect pp(redir.rdbuf());

	int program[] = { 5010, 2100, 5010, 2101, 3100, 4207, 0000, 5001, 1200, 4300 };

	s.loadProgramIntoMemory(program);
	s.disassembleProgram();
	REQUIRE(redir.str() == "1HALT\n");
}

TEST_CASE("Call and Ret"){
	Simpletron s;
	std::stringstream redir;
	cout_redirect pp(redir.rdbuf());

	int program[] = { 5005, 2400, 5001, 1200, 4008, 5060, 1200, 2500, 4300 };

	s.loadProgramIntoMemory(program);
	s.disassembleProgram();
	REQUIRE(redir.str() == "601HALT\n");
}