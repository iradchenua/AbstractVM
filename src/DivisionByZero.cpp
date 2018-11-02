#include "DivisionByZero.hpp"

DivisionByZero	& DivisionByZero::operator=(DivisionByZero const &e)
{
	std::exception::operator=(e);
	return (*this);
}

DivisionByZero::DivisionByZero() {};
DivisionByZero::~DivisionByZero() throw() {};
DivisionByZero::DivisionByZero(DivisionByZero const & e) {
	*this = e;
}

const char *DivisionByZero:: what(void) const throw() {
	return ("division by zero");
}

