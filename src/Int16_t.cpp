#include "Int16_t.hpp"
#include <iostream>

eOperandType Int16_t::getType(void) const {
	return (Int16);
}

Int16_t::Int16_t(std::string const strVal) : AOperand<int16_t>(strVal) {

}

Int16_t::Int16_t() {

}

Int16_t::~Int16_t() {

}
