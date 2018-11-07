#include <iostream>
#ifndef EXCEPTIONS_HPP
#define EXCEPTIONS_HPP

struct Exceptions {

	class Out: public std::overflow_error {
		public:
			Out(void);
			Out(std::string const & what_arg);

			Out(Out const & e);
			~Out(void) throw();

			Out & operator=(const Out & e);

			virtual const char *what() const throw();
	};

	class DivisionByZero: public std::exception {
		public:
			DivisionByZero(void);

			DivisionByZero(DivisionByZero const & e);
			~DivisionByZero(void) throw();

			DivisionByZero & operator=(const DivisionByZero & e);

			virtual const char *what() const throw();
	};
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

		class NotEnoughOperands: public EmptyStack {
			public:
				NotEnoughOperands(void);

				NotEnoughOperands(NotEnoughOperands const & e);
				~NotEnoughOperands(void) throw();

				NotEnoughOperands & operator=(const NotEnoughOperands & e);

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