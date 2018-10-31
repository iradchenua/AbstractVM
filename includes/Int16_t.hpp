#include "AOperand.hpp"

#ifndef INT16_t_HPP
#define INT16_t_HPP

class Int16_t : public AOperand<int16_t> {
	public:
		eOperandType getType(void) const;
		Int16_t(std::string const strVal);
		Int16_t(void);
		~Int16_t(void);
};

#endif