#include <maths.hpp>
#include <Tintin_reporter.hpp>
#include <Matt_Exception.hpp>

Tintin_reporter::Tintin_reporter(void)
{
	int ret;

	if (!(ret = mkdir("/var/log/matt_daemon/", 0755)) || (ret && errno == EEXIST))
	{
		_fd = open("/var/log/matt_daemon/matt_daemon.log", O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (_fd != -1)
		{
			chmod("/var/log/matt_daemon/matt_daemon.log", 0644);
			return ;
		}
		std::cout << "Throwing excpetion" << std::endl;
		throw Matt_Exception("Can't create /var/log/matt_daemon/matt_daemon.log");
	}
}

Tintin_reporter::Tintin_reporter(Tintin_reporter const & src) : _fd(src._fd)
{
}

Tintin_reporter::~Tintin_reporter(void)
{
	close(_fd);
}

Tintin_reporter & Tintin_reporter::operator=(Tintin_reporter const & rhs)
{
	this->_fd = rhs._fd;
	return (*this);
}


void	Tintin_reporter::log(int type, std::string str) const
{
	dprintf(_fd, "%s %s - %s\n", getTime().c_str(), getTypeStr(type).c_str(), str.c_str());
}

std::string	Tintin_reporter::getTypeStr(int type) const
{
	if (type == ERROR_LOG)
		return ("\033[;31m[ ERROR ]\033[0m");
	else if (type == INFO_LOG)
		return ("\033[;34m[ INFO ]\033[0m");
	else if (type == GREEN_LOG)
		return ("\033[;32m[ CONNECT ]\033[0m");
	else if (type == DISCO_LOG)
		return ("\033[;32m[ DISCONNECT ]\033[0m");
	return ("\033[;34m[ INFO ]\033[0m");
}

std::string	Tintin_reporter::getTime(void) const
{
	char buffer[1024];

	std::time_t t = std::time(NULL);

	if (std::strftime(buffer, 1023, "[%d/%m/%Y - %H:%M:%S] :", std::localtime(&t)) == 0)
		throw Matt_Exception("Can't get time as a string.");
	return (std::string(buffer));

}