#include "memory.h"
#include <iostream> //TODO: remove


Memory::Memory(size_t memory_size) :
	variables_count(0),
	memory(std::vector<int64_t>(memory_size)) {}


int64_t Memory::get(int64_t i) const {
	if (i < 0 || i >= static_cast<int64_t>(memory.size())) {
		throw std::out_of_range("Index out of range.");
	}

	std::cerr << "get " << i << " " << memory[i] << std::endl;


	return memory[i];
}


void Memory::set(int64_t i, int64_t value) {
	if (i < 0 || i >= static_cast<int64_t>(memory.size())) {
		throw std::out_of_range("Index out of range.");
	}

	std::cerr << "set " << i << " " << value << std::endl;

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
	variables_count = 0;
    std::fill(memory.begin(), memory.end(), 0);
    indexing.clear();
}
