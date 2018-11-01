#include "IOperand.hpp"
#include "FactorySpace.hpp"
#include <iostream>
#include <limits>
#include <typeinfo>
#include <cmath>

#ifndef AOPERAND_HPP
#define AOPERAND_HPP

template <typename T>

class AOperand : public IOperand {

	private:
		eOperandType const _type;
		int const _precison;
		T  const _val;
		std::string const _strVal;

		template<typename Lambda>

		IOperand const * doOp(IOperand const & rhs, Lambda && Op) const{
			std::string resVal;
			switch(rhs.getType())  {
				case (Int16):
					resVal = std::to_string(Op(this->_val, dynamic_cast<AOperand<int16_t> const &>(rhs).getVal()));
					break;
				case (Int32):
					resVal = std::to_string(Op(this->_val, dynamic_cast<AOperand<int32_t> const &>(rhs).getVal()));
					break;
				case (Float):
					resVal = std::to_string(Op(this->_val, dynamic_cast<AOperand<float> const &>(rhs).getVal()));
					break;
				case (Double):
					resVal = std::to_string(Op(this->_val, dynamic_cast<AOperand<double> const &>(rhs).getVal()));
					break;
				default:
					resVal = std::to_string(Op(this->_val, dynamic_cast<AOperand<int8_t> const &>(rhs).getVal()));
					break;
			}
			return (factorySpace::factory.createOperand(this->biggerType(rhs), resVal));
		};

		T convertFun(std::string const strVal) {
			if (this->_type < Int32)
				return (std::stoi(strVal));
			if (this->_type == Float)
				return (std::stof(strVal));
			return (std::stod(strVal));
		};

	public:
		eOperandType getType(void) const {
			return (this->_type);
		};

		eOperandType biggerType(IOperand const & rhs) const {
			if (this->getPrecision() < rhs.getPrecision())
				return (rhs.getType());
			return (this->_type);
		};

		virtual IOperand const * operator%(IOperand const & rhs) const {
			return (this->doOp(rhs, [](auto a, auto b) {
					if (b == 0)
						throw std::invalid_argument("modulo by zero");
					return (std::fmod(a, b));
				}));
		};

		virtual IOperand const * operator/(IOperand const & rhs) const {
			return (this->doOp(rhs, [](auto a, auto b) {
				if (b == 0)
					throw std::invalid_argument("dividing by zero");
				return (a / b);
			}));
		};


		virtual IOperand const * operator*(IOperand const & rhs) const {
			return (this->doOp(rhs, [](auto a, auto b) {
				return (a * b);
			}));
		};

		virtual IOperand const * operator+(IOperand const & rhs) const {
			return (this->doOp(rhs, [](auto a, auto b) {
				return (a + b);
			}));
		};

		virtual IOperand const * operator-(IOperand const & rhs) const {
			return (this->doOp(rhs, [](auto a, auto b) {
				return (a - b);
			}));
		};

		int getPrecision(void) const {
			return (this->_precison);
		};
		AOperand(std::string const strVal, eOperandType type) :  \
		_type(type), _precison(_type), _val(this->convertFun(strVal)), _strVal(std::to_string(this->_val)) {
	
		};

		virtual ~AOperand(void) {

		};
		std::string const & toString(void) const {
			return (this->_strVal);
		};
		T const & getVal(void) const {
			return (this->_val);
		};
};

std::ostream & operator<<(std::ostream & o, IOperand const & operand);

#endif