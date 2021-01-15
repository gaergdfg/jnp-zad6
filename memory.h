#include <cstdint>
#include <vector>
#include <map>


#ifndef MEMORY_H
#define MEMORY_H


class Memory {

private:
	using type_t = int64_t;
	using dict_t = std::map<std::string, size_t>;

public:
	Memory(size_t memory_size);

	type_t get(int64_t i);

	void set(int64_t i);

private:
	std::vector<type_t> memory; // TODO: czy alias na typ vectora?
	dict_t indexing;

};


#endif /* MEMORY_H */
