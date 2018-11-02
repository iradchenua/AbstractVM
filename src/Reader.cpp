#include "Reader.hpp"

Reader::Reader() {
	this->_mute = false;
	this->_line = "";
}

Reader::~Reader() {

}

Reader::Reader(Reader const & rhs) {
	*this = rhs;
}

Reader const & Reader::operator=(Reader const & rhs) {
	static_cast<void>(rhs);
	return (*this);
}

bool Reader::checkOnEnd() {
	std::string::iterator first = this->_line.begin();
	std::string::iterator second = first + 1;
	if (first == this->_line.end() || second == this->_line.end())
		return (false);
	return (*first == ';' && *second == ';');

}

bool Reader::parseLine() {
	for (std::string::iterator it = this->_line.begin(); it != this->_line.end(); it++) {
		std::cout << *it;
	}
	return (false);
}

void Reader::read() {
	while (std::cin.good()) {
		getline(std::cin, this->_line);
		this->_line.erase(0, this->_line.find_first_not_of("\t\v\r\f "));
		if (!this->_mute) {
			if (this->_line == "exit")
				this->_mute = true;
		}
		if (this->_line == ";;") {
			std::cout << "end" << std::endl;
			break;
		}
		//std::cout << line << std::endl;
	}
}