#ifndef COMPUTER_H
#define COMPUTER_H


#include "ooasm.h"
#include "memory.h"
#include "flag_handler.h"
#include "program.h"
#include <cstdint>
#include <ostream>


class Computer {

public:
	Computer(size_t memory_size);

	void boot(const Program &program);

	void memory_dump(std::ostream &stream) const;

private:
	Memory memory;
	FlagHandler flag_handler;

};


#endif /* COMPUTER_H */
