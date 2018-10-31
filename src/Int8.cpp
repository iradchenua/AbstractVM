#include "Int8.hpp"
#include <iostream>

eOperandType Int8::getType(void) const {
	return (Int8_t);
}

Int8::Int8(std::string const strVal) : AOperand<int8_t>(strVal) {

}

Int8::Int8() {

}

Int8::~Int8() {

}
