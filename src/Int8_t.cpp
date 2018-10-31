#include "Int8_t.hpp"
#include <iostream>

eOperandType Int8_t::getType(void) const {
	return (Int8);
}

Int8_t::Int8_t(std::string const strVal) : AOperand<int8_t>(strVal) {

}

Int8_t::Int8_t() {

}

Int8_t::~Int8_t() {

}
