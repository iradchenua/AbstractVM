#include "AOperand.hpp"

std::ostream & operator<<(std::ostream & o, IOperand const & operand) {
	o << operand.toString() \
	 << " " << operand.getType();
	return (o);
}