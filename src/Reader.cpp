#include "Reader.hpp"

Reader::Reader(std::deque<IOperand const *> * const deque) : _deque(deque) {
	this->_mute = false;
	this->_line = "";
}

Reader::Reader() : _deque(nullptr) {
	this->_mute = false;
	this->_line = "";
}

Reader::~Reader() {

}

Reader::Reader(Reader const & rhs) : _deque(nullptr) {
	*this = rhs;
}

Reader const & Reader::operator=(Reader const & rhs) {
	static_cast<void>(rhs);
	return (*this);
}

void Reader::getInitializationValue(std::string const & init) const {
	std::size_t pos;
	int i = Int8;

	for ( ; i < COUNT; i++) {
		pos = init.find(factorySpace::lowStrTypes[i]);
		if (pos != std::string::npos)
			break;
	}

	if (pos == 0) {
		std::size_t openBracePos = init.find("(");
		std::size_t closeBracePos = init.find(")");

		if (openBracePos != factorySpace::lowStrTypes[i].size())
			std::cout << "not valid command" << std::endl;
		if (closeBracePos == openBracePos + 1)
			std::cout << "empty value in braces error" << std::endl;
		if (closeBracePos == std::string::npos)
		 	std::cout << "missed close brace" << std::endl;
		if (openBracePos == std::string::npos)
			std::cout << "missed open brace" << std::endl;

		this->_deque->push_front(factorySpace::factory.createOperand(static_cast<eOperandType>(i), init.substr(openBracePos + 1, closeBracePos - openBracePos - 1)));
	}
}

void Reader::dump() const {
	for (auto operand : *(this->_deque)) {
		std::cout << operand->toString() << std::endl;
	}
}

void Reader::parseLine() const {
    std::istringstream buf(this->_line);
    std::istream_iterator<std::string> beg(buf), end;

    std::vector<std::string> splited(beg, end);

    if (splited.size() >= 1) {
    	std::string const & command = splited[0];
    	if (command == "pop")
    		std::cout << "pop staff" << std::endl;
    	else if (command == "dump")
    		this->dump();
    	else if (command == "add")
    		std::cout << "add" << std::endl;
    	else if (command == "sub")
    		std::cout << "sub staff" << std::endl;
    	else if (command == "mull")
    		std::cout << "mull staff" << std::endl;
    	else if (command == "div")
    		std::cout << "div staff" << std::endl;
    	else if (command == "mod")
    		std::cout << "mod staff" << std::endl;
    	else if (command == "print")
    		std::cout << "print staff" << std::endl;
    	else if (command == "push" && splited.size() >= 2) {
    		getInitializationValue(splited[1]);
    	}
    	else
    		std::cout << "error invalid command" << std::endl;

		for(std::vector<std::string>::iterator it = splited.begin() + 1; it != splited.end(); it++) {
		    if (!(*it).empty())
				if ((*it).at(0) == ';')
					break;
		}
    }

}

void Reader::read() {

	while (std::cin.good()) {
		getline(std::cin, this->_line);
		this->_line.erase(0, this->_line.find_first_not_of("\t\v\r\f "));

		if (this->_line == ";;") {
			std::cout << "end" << std::endl;
			break;
		}

		if (!this->_mute && !this->_line.empty()) {
			if (this->_line.at(0) == ';')
				continue ;
			else if (this->_line == "exit")
				this->_mute = true;
			else {
				this->parseLine();
			}
		}
		//std::cout << line << std::endl;
	}
}