#include "computer.h"


Computer::Computer(size_t memory_size) :
	memory(Memory(memory_size)),
	flag_handler(FlagHandler()) {}


void Computer::boot(Program program) {
	for (auto &instruction : program) {
		instruction->evaluate(memory, flag_handler);
	}
}


void Computer::memory_dump(std::ostream &stream) const {
	for (size_t i = 0; i < memory.size(); i++) {
		stream << memory.get(i) << " ";
	}
}
