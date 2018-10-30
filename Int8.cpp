#include "Int8.hpp"

Int8::Int8() : _strVal("Int8") {

}

Int8::~Int8() {

}

std::string const & Int8::toString(void) const {
	return (this->_strVal);
}