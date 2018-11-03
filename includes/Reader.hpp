#include "FactorySpace.hpp"
#include <deque>
#include <sstream>
#include <vector>
#include <iterator>
#include <map>

#ifndef READER_HPP
#define READER_HPP

class Reader {
	private:

		typedef void (Reader::*noArgumentFun)();

		std::stringstream _messages;
		std::string _line;
		bool 		_mute;
		std::deque<IOperand const *> * const _deque;

		IOperand const *_lhs;
		IOperand const *_rhs;

		static std::map<std::string, noArgumentFun> _mapNoArgumentFun;

		Reader(Reader const & rhs);
		Reader();
		Reader const & operator=(Reader const & rhs);

		void parseLine();
		void getInitializationValue(std::string const & init) const;

		void sub();
		void add();
		void mul();
		void div();
		void mod();
		
		void dump();
		void pop();

		void searchPosOfType(std::string const & init, std::size_t & pos, int & type) const;

		void checkEmpty() const;

		void getLRhs();
		void clearLRhs();

	public:
		Reader(std::deque<IOperand const *> * const deque);
		~Reader();
		void read();


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
};

#endif