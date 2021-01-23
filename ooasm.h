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

	virtual int64_t evaluate_rvalue(const Memory &memory) const = 0;

};

using RValue_t = std::shared_ptr<RValue>;


class LValue : public RValue {

public:
	virtual ~LValue() = default;

	virtual void set_lvalue(Memory &memory, int64_t value) const = 0;

};

using LValue_t = std::shared_ptr<LValue>;


class Num final : public RValue {

public:
	Num(int64_t val) : val(val) {}

	virtual int64_t evaluate_rvalue(const Memory &memory) const override;

private:
	int64_t val;

};


class Mem final : public LValue {

public:
	Mem(RValue_t addr) : addr(addr) {}

	virtual void set_lvalue(Memory &memory, int64_t value) const override;

	virtual int64_t evaluate_rvalue(const Memory &memory) const override;

private:
	RValue_t addr;
};


class Lea final : public RValue {

public:
	Lea(Id id) : id(id) {}

	~Lea() = default;

	virtual int64_t evaluate_rvalue(const Memory &memory) const override;

private:
	Id id;

};


/* =============== OOASM Instructions =============== */

class OOASMInstruction {

public:
	virtual ~OOASMInstruction() = default;

	virtual void evaluate_initialise(
		[[maybe_unused]] Memory &memory,
		[[maybe_unused]] FlagHandler &flag_handler
	) const {};

	virtual void evaluate_execute(
		[[maybe_unused]] Memory &memory,
		[[maybe_unused]] FlagHandler &flag_handler
	) const {};

};


class Data final : public OOASMInstruction {

public:
	Data(Id id, std::shared_ptr<Num> val) : id(id), val(val) {}

	~Data() = default;

	virtual void evaluate_initialise(Memory &memory, FlagHandler &flag_handler) const override;

private:
	Id id;
	std::shared_ptr<Num> val;

};


class Mov final : public OOASMInstruction {

public:
	Mov(LValue_t dst, RValue_t src) : dst(dst), src(src) {}

	~Mov() = default;

	virtual void evaluate_execute(Memory &memory, FlagHandler &flag_handler) const override;

private:
	LValue_t dst;
	RValue_t src;

};


class Add final : public OOASMInstruction {

public:
	Add(LValue_t arg1, RValue_t arg2) : arg1(arg1), arg2(arg2) {}
	
	~Add() = default;

	virtual void evaluate_execute(Memory &memory, FlagHandler &flag_handler) const override;

private:
	LValue_t arg1;
	RValue_t arg2;

};


class Sub final : public OOASMInstruction {

public:
	Sub(LValue_t arg1, RValue_t arg2) : arg1(arg1), arg2(arg2) {}

	~Sub() = default;

	virtual void evaluate_execute(Memory &memory, FlagHandler &flag_handler) const override;

private:
	LValue_t arg1;
	RValue_t arg2;

};


class Inc final : public OOASMInstruction {
	
public:
	Inc(LValue_t arg) : arg(arg) {}

	~Inc() = default;

	virtual void evaluate_execute(Memory &memory, FlagHandler &flag_handler) const override;

private:
	LValue_t arg;

};


class Dec final : public OOASMInstruction {
	
public:
	Dec(LValue_t arg) : arg(arg) {}

	~Dec() = default;

	virtual void evaluate_execute(Memory &memory, FlagHandler &flag_handler) const override;

private:
	LValue_t arg;

};


class One final : public OOASMInstruction {

public:
	One(LValue_t arg) : arg(arg) {}

	~One() = default;

	virtual void evaluate_execute(Memory &memory, FlagHandler &flag_handler) const override;

private:
	LValue_t arg;

};


class OneZ final : public OOASMInstruction {

public:
	OneZ(LValue_t arg) : arg(arg) {}

	~OneZ() = default;

	virtual void evaluate_execute(Memory &memory, FlagHandler &flag_handler) const override;

private:
	LValue_t arg;
};


class OneS final : public OOASMInstruction {

public:
	OneS(LValue_t arg) : arg(arg) {}

	~OneS() = default;

	virtual void evaluate_execute(Memory &memory, FlagHandler &flag_handler) const override;

private:
	LValue_t arg;
};


#endif /* OOASM_H */
