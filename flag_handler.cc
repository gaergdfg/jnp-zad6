#include "flag_handler.h"


FlagHandler::FlagHandler() : flag_zero(false), flag_sign(false) {}


// TODO: czy rzucac wyjatkami?
bool FlagHandler::get(FlagType flag_type) {
	switch (flag_type) {
		case FlagType::zero:
			return flag_zero;
		case FlagType::sign:
			return flag_sign;
		default:
			return false;
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
			break;
	}
}
