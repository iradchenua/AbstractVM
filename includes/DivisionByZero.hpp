#include <stdexcept>

#ifndef DIVISION_BY_ZERO_HPP
#define DIVISION_BY_ZERO_HPP

class DivisionByZero: public std::exception {
		public:
			DivisionByZero(void);

			DivisionByZero(DivisionByZero const & e);
			~DivisionByZero(void) throw();

			DivisionByZero & operator=(const DivisionByZero & e);

			virtual const char *what() const throw();
};

#endif