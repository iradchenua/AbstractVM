#include "Reader.hpp"
#include "AOperand.hpp"

Reader::Reader() : _deque(nullptr) {
	this->_mute = false;
	this->_line = "";
	this->_lhs = nullptr;
	this->_rhs = nullptr;
}

Reader::Reader(std::deque<IOperand const *> * const deque) : _deque(deque) {
	this->_exit = false;
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

void Reader::print() {
 	if (this->_deque->front()->getType() == Int8)
 		this->_messages << static_cast<char>(dynamic_cast<AOperand<int8_t> const *>(this->_deque->front())->getVal()) << std::endl;
 	else
 		throw Reader::BadAssert();
}

void Reader::assert(std::string const & init) {
	std::smatch pieces;

 	if (std::regex_match(init, pieces, Reader::_typePattern)) {
 		if (!this->_mute) {
	 		this->checkEmpty();
	 		if (this->_deque->front()->getType() == factorySpace::mapStringOperand.at(pieces[1])) {
	 			IOperand const *assertOperand = factorySpace::factory.createOperand(factorySpace::mapStringOperand.at(pieces[1]), pieces[pieces.size() - 1]);
	 			if (assertOperand->toString() != this->_deque->front()->toString()) {
	 				delete assertOperand;
	 				throw Reader::BadAssert(init);
	 			}
	 			delete assertOperand;
	 		}
 		}
 	}
 	else
 		throw Reader::BadAssert(init);
}

void Reader::push(std::string const & init) {
	std::smatch pieces;

 	if (std::regex_match(init, pieces, Reader::_typePattern)) {
 		if (!this->_mute) {
	 		this->_deque->push_front(\
				factorySpace::factory.createOperand(factorySpace::mapStringOperand.at(pieces[1]), pieces[pieces.size() - 1])
			);
 		}
 	}
 	else
 		throw Reader::InvalidCommand(init);
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
	this->checkEmpty();
	delete this->_deque->front();
	this->_deque->pop_front();
}

void Reader::parseLine()  {
    std::istringstream buf(this->_line);
    std::istream_iterator<std::string> beg(buf), end;

    std::vector<std::string> splited(beg, end);

    if (splited.size() >= 1) {
    	std::string const & command = splited[0];
    	if (Reader::_mapNoArgumentFun.count(command)) {
    		if (!this->_mute)
    			(this->*Reader::_mapNoArgumentFun[command])();
    	}
    	else if (splited.size() >= 2) {
	    	if (Reader::_mapArgumentFun.count(command))
	    		(this->*Reader::_mapArgumentFun[command])(splited[1]);
    	}
    	else
    		throw Reader::InvalidCommand(command);

		for(std::vector<std::string>::iterator it = splited.begin() + 1; it != splited.end(); it++) {
		    if (!(*it).empty())
				if ((*it).at(0) == ';')
					break;
		}
    }

}

void Reader::error(std::exception const & err, size_t const & numberLine) {
	this->clearLRhs();
	this->_messages << "\033[1;32mLine: " << numberLine  << "\033[0m" \
	<< ": \033[1;31mError\033[0m: " << "\033[1;96m" \
	<< err.what() << "\033[0m" << std::endl;
}

void Reader::read(const char *programName) {
	std::size_t numberLine = 0;

	std::ifstream program(programName);

	if (programName)
		if (program.bad() || !program)
			throw Reader::BadFile();

	while (1) {
		if (!program) {
			if (!std::cin.good())
				break ;
			std::cout << "\033[1;32m" << numberLine << "\033[0m: ";
			std::getline(std::cin, this->_line);
		}
		else
		{
			if (program.eof())
				break ;
			std::getline(program, this->_line);
		}

		this->_line.erase(0, this->_line.find_first_not_of("\t\v\r\f "));

		if (!program)
			if (this->_line == ";;")
				break;

		if (!this->_exit && !this->_line.empty()) {
			if (this->_line.at(0) == ';') {
				numberLine++;
				continue ;
			}
			else if (this->_line == "exit")
				this->_exit = true;
			else {
				try {
					this->parseLine();
				}
				catch (Reader::ReaderExcept const & e) {
					this->error(e, numberLine);
					this->_mute = true;
				}
				catch (std::out_of_range const & e) {
					this->error(e, numberLine);
					this->_mute = true;
				}
				catch (std::exception const & e) {
					this->error(e, numberLine);
					this->_mute = true;
				}
			}
		}
		numberLine++;
	}
	std::cout << this->_messages.str();
	if (!this->_exit)
		throw Reader::NoExit();
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

Reader::InvalidCommand::InvalidCommand(std::string const & invalidCommand) : _invalidCommand("Invalid command\e[97m: " + invalidCommand) {

};

Reader::InvalidCommand::InvalidCommand() : _invalidCommand("InvalidCommand:\e[97m ") {

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

Reader::NoExit::NoExit() {

};
Reader::NoExit::~NoExit() throw() {};

Reader::NoExit::NoExit(Reader::NoExit const & e) {
	*this = e;
}

const char *Reader::NoExit:: what(void) const throw() {
	return ("\033[1;31mno exit\033[0m");
}

Reader::NoExit	& Reader::NoExit::operator=(Reader::NoExit const &e)
{
	std::exception::operator=(e);
	return (*this);
}

Reader::BadFile::BadFile() {

};

Reader::BadFile::~BadFile() throw() {};

Reader::BadFile::BadFile(Reader::BadFile const & e) {
	*this = e;
}

const char *Reader::BadFile:: what(void) const throw() {
	return ("\033[1;31mbad program name\033[0m");
}

Reader::BadFile	& Reader::BadFile::operator=(Reader::BadFile const &e)
{
	std::exception::operator=(e);
	return (*this);
}

Reader::BadAssert::BadAssert(std::string const & badAssert) : _badAssert("Bad assert:\e[97m " + badAssert) {

};

Reader::BadAssert::BadAssert() : _badAssert("BadAssert\e[97m") {

};
Reader::BadAssert::~BadAssert() throw() {};

Reader::BadAssert::BadAssert(Reader::BadAssert const & e) {
	*this = e;
}

Reader::BadAssert	& Reader::BadAssert::operator=(Reader::BadAssert const &e)
{
	std::exception::operator=(e);
	return (*this);
}


const char *Reader::BadAssert:: what(void) const throw() {
	return (this->_badAssert.c_str());
}
std::map<std::string, Reader::noArgumentFun> Reader::_mapNoArgumentFun = \
{{"pop", &Reader::pop}, {"dump", &Reader::dump}, {"add", &Reader::add}, \
  {"sub", &Reader::sub}, {"mul", &Reader::mul}, {"div", &Reader::div}, \
 {"mod", &Reader::mod}, {"print", &Reader::print}};

std::map<std::string, Reader::argumentFun> Reader::_mapArgumentFun = \
{{"push", &Reader::push},{"assert", &Reader::assert}};

std::regex const Reader::_typePattern("^(int(8|16|32)|double|float)\\(([-+]?[0-9]*\\.?[0-9]+)\\)$");

