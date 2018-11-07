#include "IOperand.hpp"
#include "FactorySpace.hpp"
#include "Exceptions.hpp"
#include <iostream>
#include <limits>
#include <typeinfo>
#include <cmath>

#ifndef AOPERAND_HPP
#define AOPERAND_HPP

template<class T> class AOperand : public IOperand {

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

		void limitError(std::string const & strVal) {
			if (strVal[0] == '-')
					throw Exceptions::Out(std::string("underflow for type: ") + factorySpace::lowStrTypes[this->_type]);
				else
					throw Exceptions::Out(std::string("overflow for type: ") + factorySpace::lowStrTypes[this->_type]);
		}

		template<typename U>
		T checkLimit(U const & val, std::string const & strVal) {
			if (val >  std::numeric_limits<T>::max() || val < std::numeric_limits<T>::lowest())
				this->limitError(strVal);
			return (val);
		}

		T convertFun(std::string const strVal) {
			try {				
				if (this->_type < Int32)
					return (checkLimit(std::stoi(strVal), strVal));
				if (this->_type == Float)
					return (checkLimit(std::stof(strVal), strVal));
				return (checkLimit(std::stod(strVal), strVal));
			}
			catch(std::out_of_range const & e) {
				this->limitError(strVal);
			}
			return (0);
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

		std::string ownToString(T const & val) {
			if (this->_type <= Int32)
				return (std::to_string(val));
			std::string res = std::to_string(val);
			while (res.at(res.size() - 1) == '0') {
				res.pop_back();
			}
			if (res.at(res.size() - 1) == '.')
				res.push_back('0');
			return (res);
		}
	public:

		AOperand(T const & val, eOperandType type) :  \
		_type(type), _precison(_type), _val(val), _strVal(std::to_string(this->_val)) {
	
		};

		AOperand(std::string const strVal, eOperandType type) :  \
		_type(type), _precison(_type), _val(this->convertFun(strVal)), _strVal(this->ownToString(this->_val)) {
	
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
						throw Exceptions::DivisionByZero();;
					return (std::fmod(a, b));
				}));
		};

		IOperand const * operator/(IOperand const & rhs) const {
			return (this->doOp(rhs, [](auto a, auto b) {
				if (b == 0)
						throw Exceptions::DivisionByZero();;
				return (a / b);
			}));
		};

		IOperand const * max(IOperand const & rhs) const {
			return (this->doOp(rhs, [](auto a, auto b) {
				return (a > b ? a : b);
			}));
		};

		IOperand const * min(IOperand const & rhs) const {
			return (this->doOp(rhs, [](auto a, auto b) {
				return (a < b ? a : b);
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