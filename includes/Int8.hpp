#include "IOperand.hpp"

#ifndef INT8_HPP
#define INT8_HPP

class Int8 : public IOperand {
	private:
		std::string const _strVal;
	public:
		Int8(void);
		~Int8(void);
		std::string const & toString(void) const;
};

#endif