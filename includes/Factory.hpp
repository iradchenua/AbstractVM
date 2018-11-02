#include "IOperand.hpp"

#ifndef FACTORY_HPP
#define FACTORY_HPP

class Factory {
	public:

		~Factory();
		Factory();

		Factory(Factory const & rhs);
		Factory const & operator=(Factory const & rhs);

		IOperand const *createOperand(eOperandType type, std::string const & value) const;
		typedef IOperand const * (Factory::*operandCreator)(std::string const &) const;
	private:
		IOperand const *createInt8(std::string const & value) const;
		IOperand const *createInt16(std::string const & value) const;
		IOperand const *createInt32(std::string const & value) const;
		IOperand const *createFloat(std::string const & value) const;
		IOperand const *createDouble(std::string const & value) const;
		
		static const operandCreator _operandCreators[COUNT];
};

#endif