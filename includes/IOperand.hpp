#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <cstdint>

#ifndef IOPERAND_HPP
#define IOPERAND_HPP

enum eOperandType {Int8, Int16, COUNT};

class IOperand  {
	public:
		virtual int getPrecision(void) const = 0;
		virtual eOperandType getType(void) const = 0;
		virtual IOperand const * operator+(IOperand const & rhs) const = 0;
		virtual ~IOperand( void ) {};
		virtual std::string const & toString( void ) const = 0;
};

#endif