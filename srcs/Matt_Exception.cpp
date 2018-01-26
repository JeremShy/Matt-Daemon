#include <maths.hpp>
#include <Matt_Exception.hpp>

Matt_Exception::Matt_Exception(void) : _what("Default error")
{

}

Matt_Exception::Matt_Exception(std::string str) : _what(str)
{
}

Matt_Exception::Matt_Exception(Matt_Exception const & src)
{
	*this = src;
}

Matt_Exception::~Matt_Exception(void) throw()
{
}

const char* Matt_Exception::what() const throw()
{
	return _what.c_str();
}


Matt_Exception & Matt_Exception::operator=(Matt_Exception const & rhs)
{
	_what = rhs._what;
	return (*this);
}