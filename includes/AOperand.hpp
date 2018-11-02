#include "IOperand.hpp"
#include "FactorySpace.hpp"
#include "DivisionByZero.hpp"
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

		template<typename U>
		AOperand<U> const & castToReal(IOperand const & rhs) const {
			return (dynamic_cast<AOperand<U> const &>(rhs));
		};
		
		template<typename Lambda>

		IOperand const * doOp(IOperand const & rhs, Lambda && Op) const{
			std::string resVal;

			switch(rhs.getType())  {
				case (Int16):
					resVal = std::to_string(Op(this->_val, this->castToReal<int16_t>(rhs).getVal()));
					break;
				case (Int32):
					resVal = std::to_string(Op(this->_val, this->castToReal<int32_t>(rhs).getVal()));
					break;
				case (Float):
					resVal = std::to_string(Op(this->_val, this->castToReal<float>(rhs).getVal()));
					break;
				case (Double):
					resVal = std::to_string(Op(this->_val, this->castToReal<double>(rhs).getVal()));
					break;
				default:
					resVal = std::to_string(Op(this->_val, this->castToReal<int8_t>(rhs).getVal()));
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

		AOperand() : _type(Int8), _precison(_type), _val(this->convertFun("0")), _strVal(std::to_string(this->_val)) {

		};

		AOperand<T> const & operator=(AOperand<T> const & rhs) {
			static_cast<void>(rhs);
			return (*this);
		};

		AOperand(AOperand<T> const &  rhs) {
			*this = rhs;
		};
	public:


		AOperand(std::string const strVal, eOperandType type) :  \
		_type(type), _precison(_type), _val(this->convertFun(strVal)), _strVal(std::to_string(this->_val)) {
	
		};


		virtual ~AOperand(void) {

		};

		eOperandType biggerType(IOperand const & rhs) const {
			if (this->getPrecision() < rhs.getPrecision())
				return (rhs.getType());
			return (this->_type);
		};

		IOperand const * operator%(IOperand const & rhs) const {
			return (this->doOp(rhs, [](auto a, auto b) {
					if (b == 0)
						throw DivisionByZero();;
					return (std::fmod(a, b));
				}));
		};

		IOperand const * operator/(IOperand const & rhs) const {
			return (this->doOp(rhs, [](auto a, auto b) {
				if (b == 0)
						throw DivisionByZero();;
				return (a / b);
			}));
		};


		IOperand const * operator*(IOperand const & rhs) const {
			return (this->doOp(rhs, [](auto a, auto b) {
				return (a * b);
			}));
		};

		IOperand const * operator+(IOperand const & rhs) const {
			return (this->doOp(rhs, [](auto a, auto b) {
				return (a + b);
			}));
		};

		IOperand const * operator-(IOperand const & rhs) const {
			return (this->doOp(rhs, [](auto a, auto b) {
				return (a - b);
			}));
		};


		std::string const & toString(void) const {
			return (this->_strVal);
		};

		eOperandType getType(void) const {
			return (this->_type);
		}

		int getPrecision(void) const {
			return (this->_precison);
		};

		T const & getVal(void) const {
			return (this->_val);
		};
};

std::ostream & operator<<(std::ostream & o, IOperand const & operand);

#endif