#include <iostream>
#include "Int8.hpp"
#include "IOperand.hpp"

int main(void) {
	IOperand *operand = new Int8("2fasdf");

	std::cout << operand->toString() << std::endl;

	delete operand;
	return (0);
}
