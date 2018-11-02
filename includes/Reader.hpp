#include "FactorySpace.hpp"
#include <deque>
#include <sstream>
#include <vector>
#include <iterator>

#ifndef READER_HPP
#define READER_HPP

class Reader {
	private:
		std::string _line;
		bool 		_mute;
		std::deque<IOperand const *> * const _deque;

		Reader(Reader const & rhs);
		Reader();
		Reader const & operator=(Reader const & rhs);

		void parseLine() const;
		void getInitializationValue(std::string const & init) const;
		void dump() const;
	public:
		Reader(std::deque<IOperand const *> * const deque);
		~Reader();
		void read();
};

#endif