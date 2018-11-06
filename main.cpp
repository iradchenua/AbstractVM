#include <iostream>
#include "Reader.hpp"
#include "Exceptions.hpp"

int main(int ac, char **av) {

	std::deque<IOperand const *> * const deque = new std::deque<IOperand const *>();

	Reader reader(deque);

	try {
		if (ac >= 2)
			reader.read(av[1]);
		else
			reader.read();
	} 
	catch (Exceptions::NoExit const & e) {
		std::cout << e.what() << std::endl;
	}
	catch (std::exception const & e)
	{
		std::cout << e.what() << std::endl;
	}
	delete deque;
	return (0);
}
