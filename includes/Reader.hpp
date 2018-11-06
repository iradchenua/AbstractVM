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

		void dump();
		void pop();

		void checkEmpty() const;

		void getLRhs();
		void clearLRhs();

		void error(std::exception const & e, std::size_t const & numberLine);

	public:
		Reader(std::deque<IOperand const *> * const deque);
		~Reader();
		void read(const char *programName = nullptr);


		class ReaderExcept: public std::exception {
			public:
				ReaderExcept(void);

				ReaderExcept(ReaderExcept const & e);
				~ReaderExcept(void) throw();

				ReaderExcept & operator=(const ReaderExcept & e);

				virtual const char *what() const throw();
		};

		class InvalidCommand: public ReaderExcept {
			private:
				std::string const _invalidCommand;
			public:
				InvalidCommand(void);

				InvalidCommand(std::string const & invalidCommand);
				InvalidCommand(InvalidCommand const & e);
				~InvalidCommand(void) throw();

				InvalidCommand & operator=(const InvalidCommand & e);

				virtual const char *what() const throw();
		};

		class EmptyStack: public ReaderExcept {
			public:
				EmptyStack(void);

				EmptyStack(EmptyStack const & e);
				~EmptyStack(void) throw();

				EmptyStack & operator=(const EmptyStack & e);

				virtual const char *what() const throw();
		};

		class NoExit: public ReaderExcept {
			public:
				NoExit(void);

				NoExit(NoExit const & e);
				~NoExit(void) throw();

				NoExit & operator=(const NoExit & e);

				virtual const char *what() const throw();
		};

		class BadFile: public ReaderExcept {
			public:
				BadFile(void);

				BadFile(BadFile const & e);
				~BadFile(void) throw();

				BadFile & operator=(const BadFile & e);

				virtual const char *what() const throw();
		};

		class BadAssert: public ReaderExcept {
			private:
				std::string const _badAssert;
			public:
				BadAssert(void);

				BadAssert(std::string const & badAssert);
				BadAssert(BadAssert const & e);
				~BadAssert(void) throw();

				BadAssert & operator=(const BadAssert & e);

				virtual const char *what() const throw();
		};

};

#endif