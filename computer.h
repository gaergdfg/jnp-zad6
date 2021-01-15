#include "ooasm.h"
#include "memory.h"
#include "flag_handler.h"
#include "program.h"
#include <cstdint>
#include <ostream>


#ifndef COMPUTER_H
#define COMPUTER_H


class Computer {

public:
	Computer(size_t memory_size);

	void boot(Program program);

	void memory_dump(std::ostream &stream) const;

private:
	using type_t = int64_t;

	Memory memory;
	FlagHandler flag_handler;

};


#endif /* COMPUTER_H */
