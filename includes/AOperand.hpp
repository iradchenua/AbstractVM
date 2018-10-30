#include "IOperand.hpp"

template <typename T>

class AOperand : public IOperand {
	private:
		T  _val;
		std::string _strVal;
	public:
		AOperand(std::string const strVal) {
			this->_val = std::atoi(strVal.c_str());
			this->_strVal = std::to_string(this->_val);
		};
		AOperand(void) : _val(0), _strVal("0") {

		};
		virtual ~AOperand(void) {

		};
		std::string const & toString(void) const {
			return (this->_strVal);
		};
		T const & getVal(void) const {
			return (this->_val);
		}
};