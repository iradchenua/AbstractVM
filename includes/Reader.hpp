#include "FactorySpace.hpp"
#include <deque>
#include <sstream>
#include <vector>
#include <iterator>
#include <map>
#include <regex>
#include <sstream>
#include <fstream>

#ifndef READER_HPP
#define READER_HPP

class Reader {
	private:

		typedef void (Reader::*noArgumentFun)();
		typedef void (Reader::*argumentFun)(std::string const &);

		std::stringstream _messages;
		std::string _line;
		bool 		_mute;
		bool 		_exit;
		std::size_t _numberLine;

		std::deque<IOperand const *> * const _deque;
	
		IOperand const *_lhs;
		IOperand const *_rhs;

		static std::map<std::string, noArgumentFun> _mapNoArgumentFun;
		static std::map<std::string, argumentFun> _mapArgumentFun;
		static std::regex const _typePattern;

		Reader(Reader const & rhs);
		Reader();
		Reader const & operator=(Reader const & rhs);

		void parseLine();
		void push(std::string const & init);
		void assert(std::string const & init);

		void sub();
		void add();
		void mul();
		void div();
		void mod();
		void print();

		void exit();
		void dump();
		void pop();

		void checkEmpty() const;

		void getLRhs();
		void clearLRhs();

		void error(std::exception const & e);

	public:
		Reader(std::deque<IOperand const *> * const deque);
		~Reader();
		void read(const char *programName = nullptr);
};

#endif