#include <maths.hpp>
#include <Tintin_reporter.hpp>
#include <Matt_Exception.hpp>

Tintin_reporter::Tintin_reporter(void)
{
	int ret;

	if (!(ret = mkdir("/var/log/matt_daemon/", 0755)) || (ret && errno == EEXIST))
	{
		std::cout << "here !" << std::endl;
		_fd = open("/var/log/matt_daemon/matt_daemon.log", O_WRONLY | O_CREAT, 0644);
		if (_fd != -1)
		{
			chmod("/var/log/matt_daemon/matt_daemon.log", 0644);
			return ;
		}
		std::cout << "Throwing excpetion" << std::endl;
		throw Matt_Exception("Pouet");
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