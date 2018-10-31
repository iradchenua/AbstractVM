#include <iostream>
#include "AOperand.hpp"

int main(void) {
	IOperand const *lhs = factorySpace::factory.createOperand(Int8, "12");
	IOperand const *rhs = factorySpace::factory.createOperand(Int8, "260");
	IOperand const *res = *lhs + *rhs;

	std::cout << (*lhs) << std::endl;
	std::cout << (*rhs) << std::endl;
	std::cout << (*res) << std::endl;

	delete res;
	delete lhs;
	delete rhs;

	return (0);
}
