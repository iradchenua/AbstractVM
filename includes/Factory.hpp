#include "IOperand.hpp"

#ifndef FACTORY_HPP
#define FACTORY_HPP

class Factory {
	public:
		~Factory();
		Factory();
		IOperand const *createOperand(eOperandType type, std::string const & value) const;
		typedef IOperand const * (Factory::*operandCreator)(std::string const &) const;
	private:
		static const operandCreator _operandCreators[COUNT];
		IOperand const *createInt8(std::string const & value) const;
};

#endif