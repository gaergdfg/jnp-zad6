#ifndef OOASM_H
#define OOASM_H


#include "id.h"
#include "memory.h"
#include "flag_handler.h"
#include <string>
#include <memory>

#include <iostream> //TODO:


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

	virtual Num *clone() const override {
		std::cerr << "Num clone" << std::endl;
		return new Num(*this);
	}

	virtual int64_t evaluate_rvalue(const Memory &memory) const override;

private:
	int64_t val;

};


class Mem final : public LValue {

public:
	Mem(const RValue &addr) : addr(addr.clone()) {
		std::cerr << "CONSTRUCT" << std::endl;//TODO:
	}

	Mem(RValue *addr) : addr(addr) {}

	// Mem(Mem &&) = delete;

	virtual Mem *clone() const override { 
		std::cerr << "CLONE" << std::endl;//TODO:
		return new Mem(*this);
	}

	virtual void set_lvalue(Memory &memory, int64_t value) const override;

	virtual int64_t evaluate_rvalue(const Memory &memory) const override;

private:
	std::unique_ptr<RValue> addr;

	Mem(const Mem &other) : addr(nullptr) {
		std::cerr << "RUN" << std::endl;
		if (other.addr.get() != nullptr) {
			std::cerr << "Copying inner" << std::endl;//TODO:
			addr = std::unique_ptr<RValue>(other.addr->clone());
		}
		else {
			std::cerr << "No inner" << std::endl;//TODO:
		}
	}

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
	// Data(Id id, Num val) : id(id), val(val->clone()) {}

	Data(Id id, Num *val) : id(id), val(val) {}

	~Data() = default;

	virtual void evaluate_initialise(Memory &memory, FlagHandler &flag_handler) const override;

private:
	Id id;
	std::unique_ptr<Num> val;

};


class Mov final : public OOASMInstruction {

public:
	Mov(const LValue &dst, const RValue &src) : dst(dst.clone()), src(src.clone()) {}

	Mov(LValue *dst, RValue *src) : dst(dst), src(src) {}


	~Mov() = default;

	virtual void evaluate_execute(Memory &memory, FlagHandler &flag_handler) const override;

private:
	std::unique_ptr<LValue> dst;
	std::unique_ptr<RValue> src;

};


class Add final : public OOASMInstruction {

public:
	Add(const LValue &arg1, const RValue &arg2) : arg1(arg1.clone()), arg2(arg2.clone()) {}

	Add(LValue *arg1, RValue *arg2) : arg1(arg1), arg2(arg2) {}
	

	~Add() = default;

	virtual void evaluate_execute(Memory &memory, FlagHandler &flag_handler) const override;

private:
	std::unique_ptr<LValue> arg1;
	std::unique_ptr<RValue> arg2;

};


class Sub final : public OOASMInstruction {

public:
	Sub(const LValue &arg1, const RValue &arg2) : arg1(arg1.clone()), arg2(arg2.clone()) {}

	Sub(LValue *arg1, RValue *arg2) : arg1(arg1), arg2(arg2) {}

	~Sub() = default;

	virtual void evaluate_execute(Memory &memory, FlagHandler &flag_handler) const override;

private:
	std::unique_ptr<LValue> arg1;
	std::unique_ptr<RValue> arg2;

};


class Inc final : public OOASMInstruction {
	
public:
	Inc(const LValue &arg) : arg(arg.clone()) {}

	Inc(LValue *arg) : arg(arg) {}


	~Inc() = default;

	virtual void evaluate_execute(Memory &memory, FlagHandler &flag_handler) const override;

private:
	std::unique_ptr<LValue> arg;

};


class Dec final : public OOASMInstruction {
	
public:
	Dec(const LValue &arg) : arg(arg.clone()) {}

	Dec(LValue *arg) : arg(arg) {}


	~Dec() = default;

	virtual void evaluate_execute(Memory &memory, FlagHandler &flag_handler) const override;

private:
	std::unique_ptr<LValue> arg;

};


class One final : public OOASMInstruction {

public:
	One(const LValue &arg) : arg(arg.clone()) {}

	One(LValue *arg) : arg(arg) {}


	~One() = default;

	virtual void evaluate_execute(Memory &memory, FlagHandler &flag_handler) const override;

private:
	std::unique_ptr<LValue> arg;

};


class OneZ final : public OOASMInstruction {

public:
	OneZ(const LValue &arg) : arg(arg.clone()) {}

	OneZ(LValue *arg) : arg(arg) {}

	
	~OneZ() = default;

	virtual void evaluate_execute(Memory &memory, FlagHandler &flag_handler) const override;

private:
	std::unique_ptr<LValue> arg;
};


class OneS final : public OOASMInstruction {

public:
	OneS(const LValue &arg) : arg(arg.clone()) {}

	OneS(LValue *arg) : arg(arg) {}


	~OneS() = default;

	virtual void evaluate_execute(Memory &memory, FlagHandler &flag_handler) const override;

private:
	std::unique_ptr<LValue> arg;
};


#endif /* OOASM_H */
