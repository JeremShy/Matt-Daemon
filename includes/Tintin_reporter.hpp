#ifndef TINTIN_REPORTER_CLASS_H
# define TINTIN_REPORTER_CLASS_H

# include <string>
# include <iostream>
# include <ctime>

# define ERROR_LOG 0
# define INFO_LOG 1
# define GREEN_LOG 2
# define DISCO_LOG 3


class Tintin_reporter {
public:
	Tintin_reporter(void);
	Tintin_reporter(Tintin_reporter const & src);
	~Tintin_reporter(void);

	Tintin_reporter & operator=(Tintin_reporter const & rhs);

	void	log(int type, std::string str) const;

private:
	int	_fd;
	std::string	getTime(void) const;
	std::string	getTypeStr(int	type) const;
};

#endif