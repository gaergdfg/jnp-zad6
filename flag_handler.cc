#include "flag_handler.h"
#include <stdexcept>


FlagHandler::FlagHandler() : flag_zero(false), flag_sign(false) {}


bool FlagHandler::get(FlagType flag_type) {
	switch (flag_type) {
		case FlagType::zero:
			return flag_zero;
		case FlagType::sign:
			return flag_sign;
		default:
			throw std::invalid_argument("Invalid flag type.");
	}
}


void FlagHandler::set(FlagType flag_type, bool val) {
	switch (flag_type) {
		case FlagType::zero:
			flag_zero = val;
			break;
		case FlagType::sign:
			flag_sign = val;
			break;
		default:
			throw std::invalid_argument("Invalid flag type.");
	}
}
