#include "Reader.hpp"
#include "AOperand.hpp"
#include "Exceptions.hpp"

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
 		throw Exceptions::BadAssert();
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
	 				throw Exceptions::BadAssert(init);
	 			}
	 			delete assertOperand;
	 		}
 		}
 	}
 	else
 		throw Exceptions::BadAssert(init);
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
 		throw Exceptions::InvalidCommand(init);
}

void Reader::checkEmpty() const {
	if (this->_deque->empty())
		throw Exceptions::EmptyStack();
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
	try {
		this->checkEmpty();
		this->_lhs = this->_deque->front();
		this->_deque->pop_front();
		this->checkEmpty();
		this->_rhs = this->_deque->front();
		this->_deque->pop_front();
	}
	catch (Exceptions::NotEnoughOperands const & e) {
		throw (Exceptions::NotEnoughOperands());
	}
	catch (std::exception const & e)
	{
		throw (std::exception());
	}
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
    		throw Exceptions::InvalidCommand(command);

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
			throw Exceptions::BadFile();

	while (1) {
		if (!programName) {
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
				catch (Exceptions::ReaderExcept const & e) {
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
		throw Exceptions::NoExit();
}

std::map<std::string, Reader::noArgumentFun> Reader::_mapNoArgumentFun = \
{{"pop", &Reader::pop}, {"dump", &Reader::dump}, {"add", &Reader::add}, \
  {"sub", &Reader::sub}, {"mul", &Reader::mul}, {"div", &Reader::div}, \
 {"mod", &Reader::mod}, {"print", &Reader::print}};

std::map<std::string, Reader::argumentFun> Reader::_mapArgumentFun = \
{{"push", &Reader::push},{"assert", &Reader::assert}};

std::regex const Reader::_typePattern("^(int(8|16|32)|double|float)\\(([-+]?[0-9]*\\.?[0-9]+)\\)$");

