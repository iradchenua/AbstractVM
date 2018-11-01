#include "Factory.hpp"
#include "AOperand.hpp"

Factory::Factory() {

}

Factory::~Factory() {

}

IOperand const * Factory::createOperand(eOperandType type, std::string const & value) const {
	return ((this->*Factory::_operandCreators[type])(value));
}

IOperand const * Factory::createInt8(std::string const & value) const {
	return (new AOperand<int8_t>(value, Int8));
}

IOperand const * Factory::createInt16(std::string const & value) const {
	return (new AOperand<int16_t>(value, Int16));
}

IOperand const * Factory::createInt32(std::string const & value) const {
	return (new AOperand<int32_t>(value, Int32));
}

IOperand const * Factory::createFloat(std::string const & value) const {
	return (new AOperand<float>(value, Float));
}

IOperand const * Factory::createDouble(std::string const & value) const {
	return (new AOperand<double>(value, Double));
}

const Factory::operandCreator Factory::_operandCreators[COUNT] \
= {&Factory::createInt8, &Factory::createInt16, &Factory::createInt32, &Factory::createFloat, &Factory::createDouble};