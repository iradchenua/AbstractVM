#include "IOperand.hpp"

#ifndef INT8_HPP
#define INT8_HPP

class Int8 : public IOperand {
	private:
		int8_t  _val;
		std::string _strVal;
	public:
		Int8(std::string const strVal);
		Int8(void);
		~Int8(void);
		std::string const & toString(void) const;
};

#endif