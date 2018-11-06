#include "Factory.hpp"
#include <map>

#ifndef FACTORY_SPACE_HPP
#define FACTORY_SPACE_HPP

namespace factorySpace {
	Factory const factory;
	std::string const strTypes[] = {"Int8", "Int16", "Int32", "Float", "Double"};
	std::string const lowStrTypes[] = {"int8", "int16", "int32", "float", "double"};
	std::map<std::string, eOperandType> const mapStringOperand = {{"int8", Int8},{"int16", Int16}, {"int32", Int32} , {"float", Float}, {"double", Double}};

};

#endif