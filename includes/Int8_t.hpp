#include "AOperand.hpp"

#ifndef INT8_t_HPP
#define INT8_t_HPP

class Int8_t : public AOperand<int8_t> {
	public:
		eOperandType getType(void) const;
		Int8_t(std::string const strVal);
		Int8_t(void);
		~Int8_t(void);
};

#endif