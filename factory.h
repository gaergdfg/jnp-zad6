#ifndef FACTORY_H
#define FACTORY_H


#include "ooasm.h"


using num = Num;
using mem = Mem;
using lea = Lea;


inline Data *data(const Id &id, Num val) {
	return new Data(id, val);
}


inline Mov *mov(const LValue &dst, const RValue &src) {
	return new Mov(dst, src);
}

inline Add *add(const LValue &arg1, const RValue &arg2) {
	return new Add(arg1, arg2);
}


inline Sub *sub(const LValue &arg1, const RValue &arg2) {
	return new Sub(arg1, arg2);
}


inline Inc *inc(const LValue &arg) {
	return new Inc(arg);
}


inline Dec *dec(const LValue &arg) {
	return new Dec(arg);
}


inline One *one(const LValue &arg) {
	return new One(arg);
}


inline OneZ *onez(const LValue &arg) {
	return new OneZ(arg);
}


inline OneS *ones(const LValue &arg) {
	return new OneS(arg);
}


#endif /* FACTORY_H */