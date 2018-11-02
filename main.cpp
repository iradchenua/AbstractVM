#include <iostream>
#include "Reader.hpp"

int main(void) {
	/*IOperand const *lhs = factorySpace::factory.createOperand(Int16, "5");
	IOperand const *rhs = factorySpace::factory.createOperand(Int32, "2");
	try{
		IOperand const *res = *lhs / *rhs;

		std::cout << (*lhs) << std::endl;
		std::cout << (*rhs) << std::endl;
		std::cout << (*res) << std::endl;
		
		delete res;
	}
	catch (std::exception const & e) {
		std::cout << e.what() << std::endl;
	}
	delete lhs;
	delete rhs;*/
	std::deque<IOperand const *> * const deque = new std::deque<IOperand const *>();

	Reader reader(deque);

	reader.read();
	return (0);
}
