#include "Factory.hpp"


#ifndef FACTORY_SPACE_HPP
#define FACTORY_SPACE_HPP

namespace factorySpace {
	Factory const factory;
	std::string const strTypes[] = {"Int8", "Int16", "Int32", "Float", "Double"};
	std::string const lowStrTypes[] = {"int8", "int16", "int32", "float", "double"};
};

#endif