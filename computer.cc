#include "computer.h"


Computer::Computer(size_t memory_size) :
	memory(Memory(memory_size)),
	flag_handler(FlagHandler()) {}


void Computer::boot(const Program &program) {
	memory.reset();

	for (auto &instruction : program) {
		instruction->evaluate_initialise(memory, flag_handler);
	}
	for (auto &instruction : program) {
		instruction->evaluate_execute(memory, flag_handler);
	}
}


void Computer::memory_dump(std::ostream &stream) const {
	for (size_t i = 0; i < memory.size(); i++) {
		stream << memory.get(i) << " ";
	}
}
