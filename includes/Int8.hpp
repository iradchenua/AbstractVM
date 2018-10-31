#include "AOperand.hpp"

#ifndef INT8_HPP
#define INT8_HPP

class Int8 : public AOperand<int8_t> {
	public:
		eOperandType getType(void) const;
		Int8(std::string const strVal);
		Int8(void);
		~Int8(void);
};

#endif