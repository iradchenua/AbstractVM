#include "Exceptions.hpp"

Exceptions::Out	& Exceptions::Out::operator=(Exceptions::Out const &e)
{
	std::exception::operator=(e);
	return (*this);
}

Exceptions::Out::Out() : std::overflow_error("overflow") {

};

Exceptions::Out::Out(std::string const & what_arg) : std::overflow_error(what_arg) {

};

Exceptions::Out::~Out() throw() {

};
Exceptions::Out::Out(Exceptions::Out const & e) : std::overflow_error("overflow") {
	*this = e;
}

const char *Exceptions::Out:: what(void) const throw() {
	return (this->std::overflow_error::what());
}


Exceptions::DivisionByZero	& Exceptions::DivisionByZero::operator=(Exceptions::DivisionByZero const &e)
{
	std::exception::operator=(e);
	return (*this);
}

Exceptions::DivisionByZero::DivisionByZero() {};
Exceptions::DivisionByZero::~DivisionByZero() throw() {};
Exceptions::DivisionByZero::DivisionByZero(Exceptions::DivisionByZero const & e) {
	*this = e;
}

const char *Exceptions::DivisionByZero:: what(void) const throw() {
	return ("division by zero");
}



Exceptions::ReaderExcept & Exceptions::ReaderExcept::operator=(Exceptions::ReaderExcept const &e)
{
	std::exception::operator=(e);
	return (*this);
}

Exceptions::ReaderExcept::ReaderExcept() {

};
Exceptions::ReaderExcept::~ReaderExcept() throw() {};

Exceptions::ReaderExcept::ReaderExcept(Exceptions::ReaderExcept const & e) {
	*this = e;
}

const char *Exceptions::ReaderExcept:: what(void) const throw() {
	return ("");
}


Exceptions::InvalidCommand	& Exceptions::InvalidCommand::operator=(Exceptions::InvalidCommand const &e)
{
	std::exception::operator=(e);
	return (*this);
}

Exceptions::InvalidCommand::InvalidCommand(std::string const & invalidCommand) : _invalidCommand("Invalid command\e[97m: " + invalidCommand) {

};

Exceptions::InvalidCommand::InvalidCommand() : _invalidCommand("InvalidCommand:\e[97m ") {

};
Exceptions::InvalidCommand::~InvalidCommand() throw() {};

Exceptions::InvalidCommand::InvalidCommand(Exceptions::InvalidCommand const & e) {
	*this = e;
}

const char *Exceptions::InvalidCommand:: what(void) const throw() {
	return (this->_invalidCommand.c_str());
}


Exceptions::EmptyStack	& Exceptions::EmptyStack::operator=(Exceptions::EmptyStack const &e)
{
	std::exception::operator=(e);
	return (*this);
}

Exceptions::EmptyStack::EmptyStack() {

};
Exceptions::EmptyStack::~EmptyStack() throw() {};

Exceptions::EmptyStack::EmptyStack(Exceptions::EmptyStack const & e) {
	*this = e;
}

const char *Exceptions::EmptyStack:: what(void) const throw() {
	return ("empty stack");
}

Exceptions::NotEnoughOperands	& Exceptions::NotEnoughOperands::operator=(Exceptions::NotEnoughOperands const &e)
{
	std::exception::operator=(e);
	return (*this);
}

Exceptions::NotEnoughOperands::NotEnoughOperands() {

};
Exceptions::NotEnoughOperands::~NotEnoughOperands() throw() {};

Exceptions::NotEnoughOperands::NotEnoughOperands(Exceptions::NotEnoughOperands const & e) {
	*this = e;
}

const char *Exceptions::NotEnoughOperands:: what(void) const throw() {
	return ("not enough operands");
}

Exceptions::NoExit::NoExit() {

};
Exceptions::NoExit::~NoExit() throw() {};

Exceptions::NoExit::NoExit(Exceptions::NoExit const & e) {
	*this = e;
}

const char *Exceptions::NoExit:: what(void) const throw() {
	return ("\033[1;31mno exit\033[0m");
}

Exceptions::NoExit	& Exceptions::NoExit::operator=(Exceptions::NoExit const &e)
{
	std::exception::operator=(e);
	return (*this);
}

Exceptions::BadFile::BadFile() {

};

Exceptions::BadFile::~BadFile() throw() {};

Exceptions::BadFile::BadFile(Exceptions::BadFile const & e) {
	*this = e;
}

const char *Exceptions::BadFile:: what(void) const throw() {
	return ("\033[1;31mbad program name\033[0m");
}

Exceptions::BadFile	& Exceptions::BadFile::operator=(Exceptions::BadFile const &e)
{
	std::exception::operator=(e);
	return (*this);
}

Exceptions::BadAssert::BadAssert(std::string const & badAssert) : _badAssert("Bad assert:\e[97m " + badAssert) {

};

Exceptions::BadAssert::BadAssert() : _badAssert("BadAssert\e[97m") {

};
Exceptions::BadAssert::~BadAssert() throw() {};

Exceptions::BadAssert::BadAssert(Exceptions::BadAssert const & e) {
	*this = e;
}

Exceptions::BadAssert	& Exceptions::BadAssert::operator=(Exceptions::BadAssert const &e)
{
	std::exception::operator=(e);
	return (*this);
}


const char *Exceptions::BadAssert:: what(void) const throw() {
	return (this->_badAssert.c_str());
}