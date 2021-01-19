#include "ooasm.h"


/* =============== OOASM Elements =============== */

int64_t Num::evaluate_rvalue(const Memory &) const {
    return val;
}


int64_t Mem::evaluate_lvalue(const Memory &memory) const {
    return addr->evaluate_rvalue(memory);
}


int64_t Mem::evaluate_rvalue(const Memory &memory) const {
    return memory.get(addr->evaluate_rvalue(memory));
}


int64_t Lea::evaluate_rvalue(const Memory &memory) const {
    return memory.get_index_of_var(id);
}


/* =============== OOASM Instructions =============== */

void Data::evaluate(Memory &memory, FlagHandler &) const {
    memory.create_var(id, val.evaluate_rvalue(memory));
}


void Mov::evaluate(Memory &memory, FlagHandler &) const {
    memory.set(dst->evaluate_lvalue(memory), src->evaluate_rvalue(memory));
}


void Add::evaluate(Memory &memory, FlagHandler &flag_handler) const {
    int64_t index = arg1->evaluate_lvalue(memory);
    int64_t value_original = memory.get(index);
    int64_t value_to_add = arg2->evaluate_rvalue(memory);

    // memory.set(index, value_original + value_to_add);
    arg1.set(index, value_original + value_to_add);

    // FIXME: ustawienie flag
}


void Sub::evaluate(Memory &memory, FlagHandler &flag_handler) const {
    int64_t index = arg1->evaluate_lvalue(memory);
    int64_t value_original = memory.get(index);
    int64_t value_to_add = arg2->evaluate_rvalue(memory);

    memory.set(index, value_original - value_to_add);
    // FIXME: ustawienie flag
}
