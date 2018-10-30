#include <iostream>
#include "Int8.hpp"

int main(void) {
	Int8 *operand = new Int8("12");

	std::cout << operand->toString() << std::endl;

	delete operand;
	return (0);
}
