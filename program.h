#include "ooasm.h"
#include <cstdint>
#include <vector>


#ifndef PROGRAM_H
#define PROGRAM_H


using program = Program;


class Program {

private:
	using type_t = std::unique_ptr<OOASMInstruction>;

public:
	Program(std::initializer_list<OOASMInstruction*>);

	// OOASMInstruction *get(int64_t i); // TODO: to czy iteratory?

	using iterator = std::vector<type_t>::const_iterator;

	iterator begin() { return instructions.begin(); }

	iterator end() { return instructions.end(); }

private:
	std::vector<type_t> instructions;

};


#endif /* PROGRAM_H */
