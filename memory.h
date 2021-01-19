#include <cstdint>
#include <vector>
#include <map>


#ifndef MEMORY_H
#define MEMORY_H


class Memory {

private:
	using dict_t = std::map<std::string, size_t>;

public:
	Memory(size_t memory_size);

	int64_t get(int64_t i) const;

	void set(int64_t i, int64_t value);

	void create_var(const std::string &id, int64_t value);

	size_t get_index_of_var(const std::string &id) const;

	size_t size() const { return memory.size(); }//TODO: czy iterator?

private:
	size_t variables_count;
	std::vector<int64_t> memory;
	dict_t indexing;

};


#endif /* MEMORY_H */
