#ifndef PROGRAM_H
#define PROGRAM_H
#include "factory.h"
#include "ooasm.h"
#include <cstdint>
#include <vector>




class Program {

private:
	using type_t = std::unique_ptr<OOASMInstruction>;

public:
	Program(std::initializer_list<OOASMInstruction*> instructions) {
		for (auto x : instructions) {
			this->instructions.push_back(type_t(x));
		}
	}

	Program(const Program &) = delete;

	OOASMInstruction *get(int64_t i); // TODO: to czy iteratory?

	using iterator = std::vector<type_t>::const_iterator;

	iterator begin() const { return instructions.begin(); }

	iterator end() const { return instructions.end(); }

private:
	std::vector<type_t> instructions;

};

using program = Program;


#endif /* PROGRAM_H */


//FIXME: klasa Id