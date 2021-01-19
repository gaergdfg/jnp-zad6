#include "memory.h"
#include "flag_handler.h"
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

class RValue {

public:
	virtual ~RValue() = default;

	virtual int64_t evaluate_rvalue(const Memory &memory) const = 0;

};


class LValue : public RValue {

public:
	virtual ~LValue() = default;

	virtual void set_lvalue(Memory &memory, int64_t value) const = 0;

};


class Num final : public RValue {

public:
	Num(int64_t val);

	virtual int64_t evaluate_rvalue(const Memory &memory) const override;

private:
	int64_t val;

};


class Mem final : public LValue {

public:
	explicit Mem(RValue &addr); // TODO: czy na pewno explicit?

	~Mem() = default;

	virtual void set_lvalue(Memory &memory, int64_t value) const override;

	virtual int64_t evaluate_rvalue(const Memory &memory) const override;

private:
	using placeholder = std::unique_ptr<RValue>; // FIXME: zmienic nazwe typu
	placeholder addr;

};


class Lea final : public RValue {

public:
	Lea(const std::string &id); // TODO: sprawdzenie id

	~Lea() = default;

	virtual int64_t evaluate_rvalue(const Memory &memory) const override;

private:
	std::string id;

};


/* =============== OOASM Instructions =============== */

class OOASMInstruction {

public:
	virtual ~OOASMInstruction() = default;

	virtual void evaluate(Memory &memory, FlagHandler &flag_handler) const = 0;

};


class Data final : public OOASMInstruction {

public:
	Data(const std::string &id, Num val); // TODO: sprawdzenie id

	~Data() = default;

	virtual void evaluate(Memory &memory, FlagHandler &flag_handler) const override; // TODO: flagi jako argumenty + pamiec

private:
	std::string id;
	Num val; // TODO: unique_ptr<Num>?

};


class Mov final : public OOASMInstruction {

public:
	Mov(LValue &dst, RValue &src);

	~Mov() = default;

	virtual void evaluate(Memory &memory, FlagHandler &flag_handler) const override; // TODO: flagi jako argumenty + pamiec

private:
	LValue *dst; // TODO: unique_ptr<LValue>?
	RValue *src; // TODO: unique_ptr<RValue>?

};


class Add final : public OOASMInstruction {

public:
	Add(LValue &arg1, RValue &arg2);

	~Add() = default;

	virtual void evaluate(Memory &memory, FlagHandler &flag_handler) const override; // TODO: flagi jako argumenty + pamiec

private:
	LValue *arg1; // TODO: unique_ptr<LValue>?
	RValue *arg2; // TODO: unique_ptr<RValue>?

};


class Sub final : public OOASMInstruction {

public:
	Sub(LValue &arg1, RValue &arg2);

	~Sub() = default;

	virtual void evaluate(Memory &memory, FlagHandler &flag_handler) const override; // TODO: flagi jako argumenty + pamiec

private:
	LValue *arg1; // TODO: unique_ptr<LValue>?
	RValue *arg2; // TODO: unique_ptr<RValue>?

};


class Inc final : public OOASMInstruction {
	
public:
	Inc(LValue &arg);

	~Inc() = default;

	virtual void evaluate(Memory &memory, FlagHandler &flag_handler) const override; // TODO: flagi jako argumenty + pamiec

private:
	LValue *arg; // TODO: unique_ptr<LValue>?

};


class Dec final : public OOASMInstruction {
	
public:
	Dec(LValue &arg);

	~Dec() = default;

	virtual void evaluate(Memory &memory, FlagHandler &flag_handler) const override; // TODO: flagi jako argumenty + pamiec

private:
	LValue *arg; // TODO: unique_ptr<LValue>?

};


class One final : public OOASMInstruction {

public:
	One(LValue &arg);

	~One() = default;

	virtual void evaluate(Memory &memory, FlagHandler &flag_handler) const override; // TODO: flagi jako argumenty + pamiec

private:
	LValue *arg; // TODO: unique_ptr<LValue>?

};


class OneZ final : public OOASMInstruction {

public:
	OneZ(LValue &arg);
	
	~OneZ() = default;

	virtual void evaluate(Memory &memory, FlagHandler &flag_handler) const override; // TODO: flagi jako argumenty + pamiec

private:
	LValue *arg; // TODO: unique_ptr<LValue>?

};


class OneS final : public OOASMInstruction {

public:
	OneS(LValue &arg);

	~OneS() = default;

	virtual void evaluate(Memory &memory, FlagHandler &flag_handler) const override; // TODO: flagi jako argumenty + pamiec

private:
	LValue *arg; // TODO: unique_ptr<LValue>?

};


#endif /* OOASM_H */
