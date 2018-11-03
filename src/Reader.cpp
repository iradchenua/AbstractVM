#include "Reader.hpp"
#include <sstream> 

Reader::Reader(std::deque<IOperand const *> * const deque) : _deque(deque) {
	this->_mute = false;
	this->_line = "";
	this->_lhs = nullptr;
	this->_rhs = nullptr;
}

Reader::Reader() : _deque(nullptr) {
	this->_mute = false;
	this->_line = "";
	this->_lhs = nullptr;
	this->_rhs = nullptr;
}

Reader::~Reader() {
	this->clearLRhs();
	for (auto operand : *(this->_deque)) {
		delete operand;
	}
	delete this->_deque;
}

Reader::Reader(Reader const & rhs) : _deque(nullptr) {
	*this = rhs;
}

Reader const & Reader::operator=(Reader const & rhs) {
	static_cast<void>(rhs);
	return (*this);
}

void Reader::searchPosOfType(std::string const & init, std::size_t & pos, int & type) const {
	type = Int8;
	for ( ; type < COUNT; type++) {
		pos = init.find(factorySpace::lowStrTypes[type]);
		if (pos != std::string::npos)
			break;
	}
}

void Reader::getInitializationValue(std::string const & init) const {
	std::size_t pos;
	int type;

	this->searchPosOfType(init, pos, type);

	if (pos != 0)
		throw Reader::InvalidCommand(init);

	std::size_t openBracePos = init.find("(");
	std::size_t closeBracePos = init.find(")");

	if (openBracePos != factorySpace::lowStrTypes[type].size())
		throw Reader::InvalidCommand(init);
	if (closeBracePos == openBracePos + 1)
		std::cout << "empty value in braces error" << std::endl;
	if (closeBracePos == std::string::npos)
	 	std::cout << "missed close brace" << std::endl;
	if (openBracePos == std::string::npos)
		std::cout << "missed open brace" << std::endl;

	this->_deque->push_front(\
		factorySpace::factory.createOperand(static_cast<eOperandType>(type), init.substr(openBracePos + 1, closeBracePos - openBracePos - 1))
	);
}

void Reader::checkEmpty() const {
	if (this->_deque->empty())
		throw EmptyStack();
}

void Reader::dump() {
	std::string wtf;

	for (auto operand : *(this->_deque)) {
		this->_messages << operand->toString() << std::endl;
	}
}

void Reader::clearLRhs() {
	if (this->_lhs)
		delete this->_lhs;
	if (this->_rhs)
		delete this->_rhs;
	this->_lhs = nullptr;
	this->_rhs = nullptr;
}

void Reader::getLRhs() {
	this->checkEmpty();
	this->_lhs = this->_deque->front();
	this->_deque->pop_front();
	this->checkEmpty();
	this->_rhs = this->_deque->front();
	this->_deque->pop_front();
}

void Reader::mod() {
	this->getLRhs();
	this->_deque->push_back(*this->_rhs % *this->_lhs);
	this->clearLRhs();
}

void Reader::div() {
	this->getLRhs();
	this->_deque->push_back(*this->_rhs / *this->_lhs);
	this->clearLRhs();
}

void Reader::mul() {
	this->getLRhs();
	this->_deque->push_back(*this->_rhs * *this->_lhs);
	this->clearLRhs();
}

void Reader::sub() {
	this->getLRhs();
	this->_deque->push_back(*this->_rhs - *this->_lhs);
	this->clearLRhs();
}

void Reader::add() {
	this->getLRhs();
	this->_deque->push_back(*this->_lhs + *this->_rhs);
	this->clearLRhs();
}

void Reader::pop() {
	delete this->_deque->front();
	this->_deque->pop_front();
}

void Reader::parseLine()  {
    std::istringstream buf(this->_line);
    std::istream_iterator<std::string> beg(buf), end;

    std::vector<std::string> splited(beg, end);

    if (splited.size() >= 1) {
    	std::string const & command = splited[0];
    	if (Reader::_mapNoArgumentFun.count(command))
    		(this->*Reader::_mapNoArgumentFun[command])();
    	else if (command == "push" && splited.size() >= 2)
    		getInitializationValue(splited[1]);
    	else
    		throw Reader::InvalidCommand(command);

		for(std::vector<std::string>::iterator it = splited.begin() + 1; it != splited.end(); it++) {
		    if (!(*it).empty())
				if ((*it).at(0) == ';')
					break;
		}
    }

}

void Reader::read() {
	std::size_t numberLine = 0;

	while (std::cin.good()) {

		getline(std::cin, this->_line);
		this->_line.erase(0, this->_line.find_first_not_of("\t\v\r\f "));

		if (this->_line == ";;")
			break;

		if (!this->_mute && !this->_line.empty()) {
			if (this->_line.at(0) == ';')
				continue ;
			else if (this->_line == "exit")
				this->_mute = true;
			else {
				try {
					this->parseLine();
				}
				catch (Reader::ReaderExcept const & e) {
					this->clearLRhs();
					this->_messages << "Line " << numberLine \
					<< ": Error : " << e.what() << std::endl;
				}
				catch (std::exception const & e) {
					this->clearLRhs();
					this->_messages << "Line " << numberLine \
					<< ": Error : " << e.what() << std::endl;
				}
			}
		}
		numberLine++;
	}
	std::cout << this->_messages.str();
}

Reader::ReaderExcept & Reader::ReaderExcept::operator=(Reader::ReaderExcept const &e)
{
	std::exception::operator=(e);
	return (*this);
}

Reader::ReaderExcept::ReaderExcept() {

};
Reader::ReaderExcept::~ReaderExcept() throw() {};

Reader::ReaderExcept::ReaderExcept(Reader::ReaderExcept const & e) {
	*this = e;
}

const char *Reader::ReaderExcept:: what(void) const throw() {
	return ("");
}


Reader::InvalidCommand	& Reader::InvalidCommand::operator=(Reader::InvalidCommand const &e)
{
	std::exception::operator=(e);
	return (*this);
}

Reader::InvalidCommand::InvalidCommand(std::string const & invalidCommand) : _invalidCommand("Invalid command: " + invalidCommand) {

};

Reader::InvalidCommand::InvalidCommand() : _invalidCommand("InvalidCommand: ") {

};
Reader::InvalidCommand::~InvalidCommand() throw() {};

Reader::InvalidCommand::InvalidCommand(Reader::InvalidCommand const & e) {
	*this = e;
}

const char *Reader::InvalidCommand:: what(void) const throw() {
	return (this->_invalidCommand.c_str());
}


Reader::EmptyStack	& Reader::EmptyStack::operator=(Reader::EmptyStack const &e)
{
	std::exception::operator=(e);
	return (*this);
}

Reader::EmptyStack::EmptyStack() {

};
Reader::EmptyStack::~EmptyStack() throw() {};

Reader::EmptyStack::EmptyStack(Reader::EmptyStack const & e) {
	*this = e;
}

const char *Reader::EmptyStack:: what(void) const throw() {
	return ("empty stack");
}

std::map<std::string, Reader::noArgumentFun> Reader::_mapNoArgumentFun = \
{{"pop", &Reader::pop}, {"dump", &Reader::dump}, {"add", &Reader::add}, \
  {"sub", &Reader::sub}, {"mul", &Reader::mul}, {"div", &Reader::div}, \
 {"mod", &Reader::mod}};