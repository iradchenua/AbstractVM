#include "Factory.hpp"

#ifndef READER_HPP
#define READER_HPP

class Reader {
	private:
		std::string _line;
		bool 		_mute;

		Reader(Reader const & rhs);
		Reader const & operator=(Reader const & rhs);
	public:
		Reader();
		~Reader();
		void read();
		bool checkOnEnd();
		bool parseLine();
};

#endif