#include "memory.h"
#include <string>
#include <memory>


#ifndef OOASM_H
#define OOASM_H


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

class OOASMElement {

public:
	virtual ~OOASMElement() = default;

	virtual void evaluate() const = 0; // TODO: flagi jako argumenty + pamiec

};


class LValue : private OOASMElement {

public:
	virtual ~LValue() = default;

	virtual void evaluate() const = 0; // TODO: flagi jako argumenty + pamiec
	
	using OOASMElement::evaluate;
	// TODO: czy w ten sposob zachowa informacje, ze evaluate jest virtual?
	// kwestia - private/public dziedziczenie

};


class RValue : private OOASMElement {

public:
	virtual ~RValue() = default;

	virtual void evaluate() const = 0; // TODO: flagi jako argumenty + pamiec
	
	using OOASMElement::evaluate;
	// TODO: czy w ten sposob zachowa informacje, ze evaluate jest virtual?
	// kwestia - private/public dziedziczenie

};


class Num : private RValue {

public:
	Num(int64_t val);

	virtual void evaluate() const override; // TODO: flagi jako argumenty + pamiec

private:
	int64_t val;

};


class Mem : virtual LValue, virtual RValue {

public:
	explicit Mem(RValue &addr); // TODO: czy na pewno explicit?

	virtual void evaluate() const override; // TODO: flagi jako argumenty + pamiec

private:
	using placeholder = std::unique_ptr<RValue>; // FIXME: zmienic nazwe typu
	placeholder addr;

};


class Lea : private RValue {

public:
	Lea(std::string &id);

	virtual void evaluate() const override; // TODO: flagi jako argumenty + pamiec

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
	Data(std::string &id, Num val);

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
