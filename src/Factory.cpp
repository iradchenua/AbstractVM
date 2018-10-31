#include "Factory.hpp"
#include "Int8_t.hpp"
#include "Int16_t.hpp"

Factory::Factory() {

}

Factory::~Factory() {

}

IOperand const * Factory::createOperand(eOperandType type, std::string const & value) const {
	return ((this->*Factory::_operandCreators[type])(value));
}

IOperand const * Factory::createInt8(std::string const & value) const {
	return (new Int8_t(value));
}

IOperand const * Factory::createInt16(std::string const & value) const {
	return (new Int16_t(value));
}

const Factory::operandCreator Factory::_operandCreators[COUNT] \
= {&Factory::createInt8, &Factory::createInt16};