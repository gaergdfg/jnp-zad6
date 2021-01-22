#include "factory.h"

Data *data(const std::string &id, Num val) {
	return new Data(id, val);
}

Mov *mov(const LValue &dst, const RValue &src) {
	return new Mov(dst, src);
}

Add *add(const LValue &arg1, const RValue &arg2) {
	return new Add(arg1, arg2);
}

Sub *sub(const LValue &arg1, const RValue &arg2) {
	return new Sub(arg1, arg2);
}

Inc *inc(const LValue &arg) {
	return new Inc(arg);
}

Dec *dec(const LValue &arg) {
	return new Dec(arg);
}

One *one(const LValue &arg) {
	return new One(arg);
}

OneZ *onez(const LValue &arg) {
	return new OneZ(arg);
}

OneS *ones(const LValue &arg) {
	return new OneS(arg);
}