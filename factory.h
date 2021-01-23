#ifndef FACTORY_H
#define FACTORY_H


#include "ooasm.h"

inline std::shared_ptr<Num> num(int64_t val) {
	return std::make_shared<Num>(val);
}

inline std::shared_ptr<Lea> lea(const Id &id) {
	return std::make_shared<Lea>(id);
}

inline std::shared_ptr<Mem> mem(RValue_t addr) {
	return std::make_shared<Mem>(addr);
}

inline std::shared_ptr<Data> data(const Id &id, std::shared_ptr<Num> val) {
	return std::make_shared<Data>(id, val);
}

inline std::shared_ptr<Mov> mov(LValue_t dst, RValue_t src) {
	return std::make_shared<Mov>(dst, src);
}

inline std::shared_ptr<Add> add(LValue_t arg1, RValue_t arg2) {
	return std::make_shared<Add>(arg1, arg2);
}

inline std::shared_ptr<Sub> sub(LValue_t arg1, RValue_t arg2) {
	return std::make_shared<Sub>(arg1, arg2);
}

inline std::shared_ptr<Inc> inc(LValue_t arg) {
	return std::make_shared<Inc>(arg);
}

inline std::shared_ptr<Dec> dec(LValue_t arg) {
	return std::make_shared<Dec>(arg);
}

inline std::shared_ptr<One> one(LValue_t arg) {
	return std::make_shared<One>(arg);
}

inline std::shared_ptr<OneZ> onez(LValue_t arg) {
	return std::make_shared<OneZ>(arg);
}

inline std::shared_ptr<OneS> ones(LValue_t arg) {
	return std::make_shared<OneS>(arg);
}


#endif /* FACTORY_H */