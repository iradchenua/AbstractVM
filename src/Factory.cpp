#include "Factory.hpp"
#include "Int8.hpp"

Factory::Factory() {

}

Factory::~Factory() {

}

IOperand const * Factory::createOperand(eOperandType type, std::string const & value) const {
	return ((this->*Factory::_operandCreators[type])(value));
}

IOperand const * Factory::createInt8(std::string const & value) const {
	return (new Int8(value));
}

const Factory::operandCreator Factory::_operandCreators[COUNT] \
= {&Factory::createInt8};