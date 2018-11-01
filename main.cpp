#include <iostream>
#include "AOperand.hpp"

int main(void) {
	IOperand const *lhs = factorySpace::factory.createOperand(Double, "320.5");
	IOperand const *rhs = factorySpace::factory.createOperand(Float, "256.5");
	IOperand const *res = *lhs % *rhs;

	std::cout << (*lhs) << std::endl;
	std::cout << (*rhs) << std::endl;
	std::cout << (*res) << std::endl;
	
	delete res;
	delete lhs;
	delete rhs;

	return (0);
}
