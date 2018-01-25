#ifndef TINTIN_REPORTER_CLASS_H
# define TINTIN_REPORTER_CLASS_H

# include <string>
# include <iostream>

class Tintin_reporter {
public:
	Tintin_reporter(void);
	Tintin_reporter(Tintin_reporter const & src);
	~Tintin_reporter(void);

	Tintin_reporter & operator=(Tintin_reporter const & rhs);
private:
	int	fd;
};
std::ostream& operator<<(std::ostream& os, const Tintin_reporter & rhs);
#endif
