#ifndef OOASM_H
#define OOASM_H
#include "memory.h"
#include "flag_handler.h"
#include <string>
#include <memory>

// TODO: co z wydzieleniem klasy identyfikatora?

// TODO: to chyba powinny byc funkcje-wrappery konstruktorow w jakims factory.h


/* =============== OOASM Elements =============== */

class RValue {

public:
	virtual ~RValue() = default;

	virtual RValue *clone() const = 0;

	virtual int64_t evaluate_rvalue(const Memory &memory) const = 0;

};


class LValue : public RValue {

public:
	virtual ~LValue() = default;

	virtual LValue *clone() const = 0;

	virtual void set_lvalue(Memory &memory, int64_t value) const = 0;

};


class Num final : public RValue {

public:
	Num(int64_t val) : val(val) {}

	virtual Num *clone() const override { return new Num(*this); }

	virtual int64_t evaluate_rvalue(const Memory &memory) const override;

private:
	int64_t val;

};


class Mem final : public LValue {

public:
	explicit Mem(const RValue &addr) : addr(addr.clone()) {} // TODO: czy na pewno explicit?

	Mem(const Mem &other) : addr(nullptr) {
		if (other.addr.get() != nullptr) {
			addr = placeholder(other.addr->clone());
		}
	}

	virtual Mem *clone() const override { return new Mem(*this); }

	virtual void set_lvalue(Memory &memory, int64_t value) const override;

	virtual int64_t evaluate_rvalue(const Memory &memory) const override;

private:
	using placeholder = std::unique_ptr<RValue>; // FIXME: zmienic nazwe typu
	placeholder addr;

};


class Lea final : public RValue {

public:
	Lea(const std::string &id) : id(id) {} // TODO: sprawdzenie id

	~Lea() = default;

	virtual Lea *clone() const override { return new Lea(*this); }


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
	Data(const std::string &id, Num val) : id(id), val(val) {} // TODO: sprawdzenie id

	~Data() = default;

	virtual void evaluate(Memory &memory, FlagHandler &flag_handler) const override; // TODO: flagi jako argumenty + pamiec

private:
	std::string id;
	Num val; // TODO: unique_ptr<Num>?

};


class Mov final : public OOASMInstruction {

public:
	Mov(const LValue &dst, const RValue &src) : dst(dst.clone()), src(src.clone()) {}

	~Mov() = default;

	virtual void evaluate(Memory &memory, FlagHandler &flag_handler) const override; // TODO: flagi jako argumenty + pamiec

private:
	std::unique_ptr<LValue> dst; // TODO: unique_ptr<LValue>?
	std::unique_ptr<RValue> src; // TODO: unique_ptr<RValue>?

};


class Add final : public OOASMInstruction {

public:
	Add(const LValue &arg1, const RValue &arg2) : arg1(arg1.clone()), arg2(arg2.clone()) {}

	~Add() = default;

	virtual void evaluate(Memory &memory, FlagHandler &flag_handler) const override; // TODO: flagi jako argumenty + pamiec

private:
	std::unique_ptr<LValue> arg1; // TODO: unique_ptr<LValue>?
	std::unique_ptr<RValue> arg2; // TODO: unique_ptr<RValue>?

};


class Sub final : public OOASMInstruction {

public:
	Sub(const LValue &arg1, const RValue &arg2) : arg1(arg1.clone()), arg2(arg2.clone()) {}

	~Sub() = default;

	virtual void evaluate(Memory &memory, FlagHandler &flag_handler) const override; // TODO: flagi jako argumenty + pamiec

private:
	std::unique_ptr<LValue> arg1; // TODO: unique_ptr<LValue>?
	std::unique_ptr<RValue> arg2; // TODO: unique_ptr<RValue>?

};


class Inc final : public OOASMInstruction {
	
public:
	Inc(const LValue &arg) : arg(arg.clone()) {}

	~Inc() = default;

	virtual void evaluate(Memory &memory, FlagHandler &flag_handler) const override; // TODO: flagi jako argumenty + pamiec

private:
	std::unique_ptr<LValue> arg;

};


class Dec final : public OOASMInstruction {
	
public:
	Dec(const LValue &arg) : arg(arg.clone()) {}

	~Dec() = default;

	virtual void evaluate(Memory &memory, FlagHandler &flag_handler) const override; // TODO: flagi jako argumenty + pamiec

private:
	std::unique_ptr<LValue> arg; // TODO: unique_ptr<LValue>?

};


class One final : public OOASMInstruction {

public:
	One(const LValue &arg) : arg(arg.clone()) {}

	~One() = default;

	virtual void evaluate(Memory &memory, FlagHandler &flag_handler) const override; // TODO: flagi jako argumenty + pamiec

private:
	std::unique_ptr<LValue> arg; // TODO: unique_ptr<LValue>?

};


class OneZ final : public OOASMInstruction {

public:
	OneZ(const LValue &arg) : arg(arg.clone()) {}
	
	~OneZ() = default;

	virtual void evaluate(Memory &memory, FlagHandler &flag_handler) const override; // TODO: flagi jako argumenty + pamiec

private:
	std::unique_ptr<LValue> arg; // TODO: unique_ptr<LValue>?
};


class OneS final : public OOASMInstruction {

public:
	OneS(const LValue &arg) : arg(arg.clone()) {}

	~OneS() = default;

	virtual void evaluate(Memory &memory, FlagHandler &flag_handler) const override; // TODO: flagi jako argumenty + pamiec

private:
	std::unique_ptr<LValue> arg; // TODO: unique_ptr<LValue>?
};


#endif /* OOASM_H */
