#include "ooasm.h"

int64_t Mem::evaluate_lvalue(const Memory &memory) const {
    return addr->evaluate_rvalue(memory);
}

int64_t Mem::evaluate_rvalue(const Memory &memory) const {
    return memory.get(addr->evaluate_rvalue(memory));
}

int64_t Lea::evaluate_rvalue(const Memory &memory) const {
    return memory.get_index_of_var(id);
}

void Data::evaluate(Memory &memory, FlagHandler &) const {
    memory.create_var(id, val.evaluate_rvalue(memory));
}

void Mov::evaluate(Memory &memory, FlagHandler &) const {
    memory.set(dst->evaluate_lvalue(memory), src->evaluate_rvalue(memory));
}

void Add::evaluate(Memory &memory, FlagHandler &flag_handler) const {
// TODO
}