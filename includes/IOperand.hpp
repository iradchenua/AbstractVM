#include <string>
#include <stdio.h>
#include <stdlib.h>

#ifndef IOPERAND_HPP
#define IOPERAND_HPP

class IOperand  {
	public:
		virtual ~IOperand( void ) {};
		virtual std::string const & toString( void ) const = 0;
};

#endif