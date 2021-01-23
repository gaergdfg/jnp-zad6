#include "memory.h"


Memory::Memory(size_t memory_size) :
	variables_count(0),
	memory(std::vector<int64_t>(memory_size)) {}


int64_t Memory::get(int64_t i) const {
	if (i < 0 || i >= static_cast<int64_t>(memory.size())) {
		throw std::out_of_range("Index out of range.");
	}

	return memory[i];
}


void Memory::set(int64_t i, int64_t value) {
	if (i < 0 || i >= static_cast<int64_t>(memory.size())) {
		throw std::out_of_range("Index out of range.");
	}

	memory[i] = value;
}


void Memory::create_var(const Id &id, int64_t value) {
	if (variables_count >= memory.size()) {
		throw std::out_of_range("Tried to allocate too many variables.");
	}

	indexing.try_emplace(id, variables_count);
	memory[variables_count++] = value;
}


size_t Memory::get_index_of_var(const Id &id) const {
	return indexing.at(id);
}


void Memory::reset() {
	for (size_t i = 0; i < memory.size(); i++) {
		memory[i] = 0;
	}
}
