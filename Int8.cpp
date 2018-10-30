#include "Int8.hpp"

Int8::Int8(std::string const strVal) : _strVal(strVal) {
	this->_val = std::atoi(this->_strVal.c_str());
	this->_strVal = std::to_string(this->_val);
}

Int8::Int8() : _val(0), _strVal("0") {

}

Int8::~Int8() {

}

std::string const & Int8::toString(void) const {
	return (this->_strVal);
}