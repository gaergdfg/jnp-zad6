#ifndef FACTORY_H
#define FACTORY_H
#include "ooasm.h"
// #include "program.h"


using num = Num;
using mem = Mem;
using lea = Lea;


Data *data(const std::string &id, Num val);

Mov *mov(const LValue &dst, const RValue &src);

Add *add(const LValue &arg1, const RValue &arg2);

Sub *sub(const LValue &arg1, const RValue &arg2);

Inc *inc(const LValue &arg);

Dec *dec(const LValue &arg);

One *one(const LValue &arg);

OneZ *onez(const LValue &arg);

OneS *ones(const LValue &arg);

#endif /* FACTORY_H */