#include "Reader.hpp"
#include "AOperand.hpp"
#include "Exceptions.hpp"

Reader::Reader() : Reader::Reader(nullptr) {

}

Reader::Reader(std::deque<IOperand const *> * const deque) : _deque(deque) {
	this->_numberLine = 0;
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

void Reader::exit() {
	this->_exit = true;
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
 		throw Exceptions::InvalidCommand(this->_line);
}

void Reader::checkEmpty() const {
	if (this->_deque->empty())
		throw Exceptions::EmptyStack();
}

void Reader::dump() {
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
	catch (Exceptions::EmptyStack const & e) {
		throw (Exceptions::NotEnoughOperands());
	}
	catch (std::exception const & e)
	{
		throw (std::exception());
	}
}

void Reader::mod() {
	this->_deque->push_back(*this->_rhs % *this->_lhs);
}

void Reader::max() {
	this->_deque->push_back(this->_rhs->max(*this->_lhs));
}

void Reader::min() {
	this->_deque->push_back(this->_rhs->min(*this->_lhs));
}

void Reader::div() {
	this->_deque->push_back(*this->_rhs / *this->_lhs);
}

void Reader::mul() {
	this->_deque->push_back(*this->_rhs * *this->_lhs);
}

void Reader::sub() {
	this->_deque->push_back(*this->_rhs - *this->_lhs);
}

void Reader::add() {
	this->_deque->push_back(*this->_lhs + *this->_rhs);
}

void Reader::pop() {
	this->checkEmpty();
	delete this->_deque->front();
	this->_deque->pop_front();
}

void Reader::parseLine()  {
    std::istringstream buf(this->_line);
    std::istream_iterator<std::string> beg(buf), end;

    Reader::noArgumentFun noArg = nullptr;
    Reader::noArgumentFun operFun = nullptr;
    Reader::argumentFun withArg = nullptr;
    bool wasExit = false;

    std::vector<std::string> splited(beg, end);
    std::vector<std::string>::iterator arg = splited.end();

    for (auto it = splited.begin(); it < splited.end(); it++) {
    	if (Reader::_mapOperators.count(*it) && !noArg && !withArg && !operFun) {
    		operFun = Reader::_mapOperators[*it];
    	}
    	else if (Reader::_mapNoArgumentFun.count(*it) && !noArg && !withArg && !operFun) {
    		noArg = Reader::_mapNoArgumentFun[*it];
    		if (*it == "exit")
    			wasExit = true;
    	}
    	else if (Reader::_mapArgumentFun.count(*it) && !withArg && !noArg && !operFun)
    	{
    		withArg = Reader::_mapArgumentFun[*it];
    		arg = it + 1;
    		if (arg == splited.end())
    			throw Exceptions::InvalidCommand(this->_line);
    		it++;
    	}
    	else if (it->at(0) == ';')
    		break ;
    	else
    		throw Exceptions::InvalidCommand(this->_line);
    }
    
    if (operFun &&  (!this->_mute || wasExit)) {
    	this->getLRhs();
    	(this->*operFun)();
    	this->clearLRhs();
    }
    else if (noArg && (!this->_mute || wasExit))
    	(this->*noArg)();
    else if (withArg)
    	(this->*withArg)(*arg);
}

void Reader::error(std::exception const & err) {
	this->_mute = true;
	this->clearLRhs();
	this->_messages << "\033[1;32mLine: " << this->_numberLine  << "\033[0m" \
	<< ": \033[1;31mError\033[0m: " << "\033[1;96m" \
	<< err.what() << "\033[0m" << std::endl;
}

void Reader::read(const char *programName) {
	std::ifstream program(programName);

	if (programName)
		if (program.bad() || !program)
			throw Exceptions::BadFile();

	while (1) {
		if (!programName) {
			if (!std::cin.good())
				break ;
			std::cout << "\033[1;32m" << this->_numberLine << "\033[0m: ";
			std::getline(std::cin, this->_line);
		}
		else
		{
			if (program.eof())
				break ;
			std::getline(program, this->_line);
		}

		this->_line.erase(0, this->_line.find_first_not_of("\t\v\r\f "));
		this->_line.erase(this->_line.find_last_not_of("\t\v\r\f ")+1);

		if (!programName)
			if (this->_line == ";;")
				break;

		if (!this->_exit && !this->_line.empty()) {
			try {
				this->parseLine();
			}
			catch (Exceptions::ReaderExcept const & e) {
				this->error(e);
			}
			catch (Exceptions::Out const & e) {
				this->error(e);
			}
			catch (std::exception const & e) {
				this->error(e);
			}
		
		}
		this->_numberLine++;
	}
	std::cout << this->_messages.str();
	if (!this->_exit)
		throw Exceptions::NoExit();
}

std::map<std::string, Reader::noArgumentFun> Reader::_mapOperators = \
{{"add", &Reader::add}, {"sub", &Reader::sub}, {"mul", &Reader::mul}, {"div", &Reader::div}, \
 {"mod", &Reader::mod}, {"max", &Reader::max}, {"min", &Reader::min}};


std::map<std::string, Reader::noArgumentFun> Reader::_mapNoArgumentFun = \
{{"pop", &Reader::pop}, {"dump", &Reader::dump}, \
{"print", &Reader::print}, {"exit", &Reader::exit}};

std::map<std::string, Reader::argumentFun> Reader::_mapArgumentFun = \
{{"push", &Reader::push},{"assert", &Reader::assert}};

std::regex const Reader::_typePattern("^(int(8|16|32)|double|float)\\(([-+]?[0-9]*\\.?[0-9]+)\\)$");

