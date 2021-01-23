#ifndef OOASM_H
#define OOASM_H


#include "id.h"
#include "memory.h"
#include "flag_handler.h"
#include <string>
#include <memory>


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
	explicit Mem(const RValue &addr) : addr(addr.clone()) {}

	Mem(const Mem &other) : addr(nullptr) {
		if (other.addr.get() != nullptr) {
			addr = std::unique_ptr<RValue>(other.addr->clone());
		}
	}

	virtual Mem *clone() const override { return new Mem(*this); }

	virtual void set_lvalue(Memory &memory, int64_t value) const override;

	virtual int64_t evaluate_rvalue(const Memory &memory) const override;

private:
	std::unique_ptr<RValue> addr;

};


class Lea final : public RValue {

public:
	Lea(Id id) : id(id) {}

	~Lea() = default;

	virtual Lea *clone() const override { return new Lea(*this); }


	virtual int64_t evaluate_rvalue(const Memory &memory) const override;

private:
	Id id;

};


/* =============== OOASM Instructions =============== */

class OOASMInstruction {

public:
	virtual ~OOASMInstruction() = default;

	virtual void evaluate_initialise(Memory &memory, FlagHandler &flag_handler) const {};

	virtual void evaluate_execute(Memory &memory, FlagHandler &flag_handler) const {};

};


class Data final : public OOASMInstruction {

public:
	Data(Id id, Num val) : id(id), val(val) {}

	~Data() = default;

	virtual void evaluate_initialise(Memory &memory, FlagHandler &flag_handler) const override;

private:
	Id id;
	Num val;

};


class Mov final : public OOASMInstruction {

public:
	Mov(const LValue &dst, const RValue &src) : dst(dst.clone()), src(src.clone()) {}

	~Mov() = default;

	virtual void evaluate_execute(Memory &memory, FlagHandler &flag_handler) const override;

private:
	std::unique_ptr<LValue> dst;
	std::unique_ptr<RValue> src;

};


class Add final : public OOASMInstruction {

public:
	Add(const LValue &arg1, const RValue &arg2) : arg1(arg1.clone()), arg2(arg2.clone()) {}

	~Add() = default;

	virtual void evaluate_execute(Memory &memory, FlagHandler &flag_handler) const override;

private:
	std::unique_ptr<LValue> arg1;
	std::unique_ptr<RValue> arg2;

};


class Sub final : public OOASMInstruction {

public:
	Sub(const LValue &arg1, const RValue &arg2) : arg1(arg1.clone()), arg2(arg2.clone()) {}

	~Sub() = default;

	virtual void evaluate_execute(Memory &memory, FlagHandler &flag_handler) const override;

private:
	std::unique_ptr<LValue> arg1;
	std::unique_ptr<RValue> arg2;

};


class Inc final : public OOASMInstruction {
	
public:
	Inc(const LValue &arg) : arg(arg.clone()) {}

	~Inc() = default;

	virtual void evaluate_execute(Memory &memory, FlagHandler &flag_handler) const override;

private:
	std::unique_ptr<LValue> arg;

};


class Dec final : public OOASMInstruction {
	
public:
	Dec(const LValue &arg) : arg(arg.clone()) {}

	~Dec() = default;

	virtual void evaluate_execute(Memory &memory, FlagHandler &flag_handler) const override;

private:
	std::unique_ptr<LValue> arg;

};


class One final : public OOASMInstruction {

public:
	One(const LValue &arg) : arg(arg.clone()) {}

	~One() = default;

	virtual void evaluate_execute(Memory &memory, FlagHandler &flag_handler) const override;

private:
	std::unique_ptr<LValue> arg;

};


class OneZ final : public OOASMInstruction {

public:
	OneZ(const LValue &arg) : arg(arg.clone()) {}
	
	~OneZ() = default;

	virtual void evaluate_execute(Memory &memory, FlagHandler &flag_handler) const override;

private:
	std::unique_ptr<LValue> arg;
};


class OneS final : public OOASMInstruction {

public:
	OneS(const LValue &arg) : arg(arg.clone()) {}

	~OneS() = default;

	virtual void evaluate_execute(Memory &memory, FlagHandler &flag_handler) const override;

private:
	std::unique_ptr<LValue> arg;
};


#endif /* OOASM_H */
