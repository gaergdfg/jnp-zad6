#include "memory.h"
#include <string>
#include <memory>


#ifndef OOASM_H
#define OOASM_H

// TODO: co z wydzieleniem klasy identyfikatora?

// TODO: to chyba powinny byc funkcje-wrappery konstruktorow w jakims factory.h
using num = Num;
using mem = Mem;
using lea = Lea;

using data = Data;
using mov = Mov;

using add = Add;
using sub = Sub;
using inc = Inc;
using dec = Dec;

using one = One;
using onez = OneZ;
using ones = OneS;


/* =============== OOASM Elements =============== */

class LValue {

public:
	virtual ~LValue() = default;

	virtual int64_t evaluate_lvalue(const Memory &memory) const = 0;

};


class RValue {

public:
	virtual ~RValue() = default;

	virtual int64_t evaluate_rvalue(const Memory &memory) const = 0;

};


class Num : private RValue {

public:
	Num(int64_t val);

	virtual int64_t evaluate_rvalue(const Memory &memory) const override;

private:
	int64_t val;

};


class Mem : private LValue, private RValue {

public:
	explicit Mem(RValue &addr); // TODO: czy na pewno explicit?

	virtual int64_t evaluate_lvalue(const Memory &memory) const override;

	virtual int64_t evaluate_rvalue(const Memory &memory) const override;

private:
	using placeholder = std::unique_ptr<RValue>; // FIXME: zmienic nazwe typu
	placeholder addr;

};


class Lea : private RValue {

public:
	Lea(const std::string &id); // TODO: sprawdzenie id

	virtual int64_t evaluate_rvalue(const Memory &memory) const override;

private:
	std::string id;

};


/* =============== OOASM Instructions =============== */

class OOASMInstruction {

public:
	virtual ~OOASMInstruction() = default;

	virtual void evaluate() const = 0;

};


class Data : private OOASMInstruction {

public:
	Data(const std::string &id, Num val); // TODO: sprawdzenie id

	virtual void evaluate() const override; // TODO: flagi jako argumenty + pamiec

private:
	std::string id;
	Num val; // TODO: unique_ptr<Num>?

};


class Mov : private OOASMInstruction {

public:
	Mov(LValue &src, RValue &dst);

	virtual void evaluate() const override; // TODO: flagi jako argumenty + pamiec

private:
	LValue *src; // TODO: unique_ptr<LValue>?
	RValue *dst; // TODO: unique_ptr<RValue>?

};


class Add : private OOASMInstruction {

public:
	Add(LValue &arg1, RValue &arg2);

	virtual void evaluate() const override; // TODO: flagi jako argumenty + pamiec

private:
	LValue *arg1; // TODO: unique_ptr<LValue>?
	RValue *arg2; // TODO: unique_ptr<RValue>?

};


class Sub : private OOASMInstruction {

public:
	Sub(LValue &arg1, RValue &arg2);

	virtual void evaluate() const override; // TODO: flagi jako argumenty + pamiec

private:
	LValue *arg1; // TODO: unique_ptr<LValue>?
	RValue *arg2; // TODO: unique_ptr<RValue>?

};


class Inc : private OOASMInstruction {
	
public:
	Inc(LValue &arg);

	virtual void evaluate() const override; // TODO: flagi jako argumenty + pamiec

private:
	LValue *arg; // TODO: unique_ptr<LValue>?

};


class Dec : private OOASMInstruction {
	
public:
	Dec(LValue &arg);

	virtual void evaluate() const override; // TODO: flagi jako argumenty + pamiec

private:
	LValue *arg; // TODO: unique_ptr<LValue>?

};


class One : private OOASMInstruction {

public:
	One(LValue &arg);

	virtual void evaluate() const override; // TODO: flagi jako argumenty + pamiec

private:
	LValue *arg; // TODO: unique_ptr<LValue>?

};


class OneZ : private OOASMInstruction {

public:
	OneZ(LValue &arg);

	virtual void evaluate() const override; // TODO: flagi jako argumenty + pamiec

private:
	LValue *arg; // TODO: unique_ptr<LValue>?

};


class OneS : private OOASMInstruction {

public:
	OneS(LValue &arg);

	virtual void evaluate() const override; // TODO: flagi jako argumenty + pamiec

private:
	LValue *arg; // TODO: unique_ptr<LValue>?

};


#endif /* OOASM_H */
