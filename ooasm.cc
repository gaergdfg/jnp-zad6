#include "ooasm.h"


/* =============== Utility functions =============== */

// TODO: czy namespace/static?
void set_flags(FlagHandler &flag_handler, int64_t value) {
    flag_handler.set(FlagHandler::FlagType::zero, value == 0);
    flag_handler.set(FlagHandler::FlagType::sign, value < 0);
}

/* =============== OOASM Elements =============== */

int64_t Num::evaluate_rvalue(const Memory &) const {
    return val;
}


void Mem::set_lvalue(Memory &memory, int64_t value) const {
    memory.set(addr->evaluate_rvalue(memory), value);
}


int64_t Mem::evaluate_rvalue(const Memory &memory) const {
    return memory.get(addr->evaluate_rvalue(memory));
}


int64_t Lea::evaluate_rvalue(const Memory &memory) const {
    return memory.get_index_of_var(id);
}


/* =============== OOASM Instructions =============== */

void Data::evaluate_initialise(Memory &memory, FlagHandler &) const {
    memory.create_var(id, val.evaluate_rvalue(memory));
}


void Mov::evaluate_execute(Memory &memory, FlagHandler &) const {
    dst->set_lvalue(memory, src->evaluate_rvalue(memory));
}


void Add::evaluate_execute(Memory &memory, FlagHandler &flag_handler) const {
    int64_t value = arg1->evaluate_rvalue(memory) + arg2->evaluate_rvalue(memory);

    arg1->set_lvalue(memory, value);
    set_flags(flag_handler, value);
}


void Sub::evaluate_execute(Memory &memory, FlagHandler &flag_handler) const {
    int64_t value = arg1->evaluate_rvalue(memory) - arg2->evaluate_rvalue(memory);

    arg1->set_lvalue(memory, value);
    set_flags(flag_handler, value);
}

void Inc::evaluate_execute(Memory &memory, FlagHandler &flag_handler) const {
    int64_t value = arg->evaluate_rvalue(memory) + 1;

    arg->set_lvalue(memory, value);
    set_flags(flag_handler, value);
}

void Dec::evaluate_execute(Memory &memory, FlagHandler &flag_handler) const {
    int64_t value = arg->evaluate_rvalue(memory) - 1;

    arg->set_lvalue(memory, value);
    set_flags(flag_handler, value);
}

void One::evaluate_execute(Memory &memory, FlagHandler &flag_handler) const {
    arg->set_lvalue(memory, 1);
}

void OneZ::evaluate_execute(Memory &memory, FlagHandler &flag_handler) const {
    if (flag_handler.get(FlagHandler::FlagType::zero)) {
        arg->set_lvalue(memory, 1);
    }
}

void OneS::evaluate_execute(Memory &memory, FlagHandler &flag_handler) const {
    if (flag_handler.get(FlagHandler::FlagType::sign)) {
        arg->set_lvalue(memory, 1);
    }
}

