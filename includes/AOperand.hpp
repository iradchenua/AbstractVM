#include "IOperand.hpp"
#include "FactorySpace.hpp"
#include <iostream>
#include <limits>
#include <typeinfo>

#ifndef AOPERAND_HPP
#define AOPERAND_HPP

template <typename T>

class AOperand : public IOperand {

	private:
		int const _precison;
		T  _val;
		std::string _strVal;

	public:
		virtual IOperand const * operator+(IOperand const & rhs) const {

			std::string strRes;
			try {
				strRes	= std::to_string(this->getVal() + dynamic_cast<AOperand<int8_t> const &>(rhs).getVal());
			}
			catch (std::bad_cast const & e) {

			}
			try {
				strRes	= std::to_string(this->getVal() + dynamic_cast<AOperand<int16_t> const &>(rhs).getVal());
			}
			catch (std::bad_cast const & e) {

			}
			eOperandType type;
			if (this->getPrecision() < rhs.getPrecision())
				type = rhs.getType();
			else
				type = this->getType();
			return (factorySpace::factory.createOperand(type, strRes));
		}
		int getPrecision(void) const {
			return (_precison);
		}
		AOperand(std::string const strVal) :  _precison(sizeof(T)) {
			this->_val = std::stoi(strVal);
			if (this->_val > std::numeric_limits<T>::max() || this->_val < std::numeric_limits<T>::min())
				throw std::out_of_range("value is out of limit");
			this->_strVal = std::to_string(this->_val);
		};

		AOperand(void) : _precison(sizeof(T)), _val(0), _strVal("0") {

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