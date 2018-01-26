#ifndef MATT_EXCEPTION_HPP
# define MATT_EXCEPTION_HPP

# include <maths.hpp>

class Matt_Exception : public std::exception
{
public:
	Matt_Exception(void);
	Matt_Exception(std::string str);
	Matt_Exception(Matt_Exception const & src);
	~Matt_Exception(void) throw();

	Matt_Exception & operator=(Matt_Exception const & rhs);
 	virtual const char* what() const throw();

private:
	std::string _what;
};


// Class A
// {
// 	print {
// 		coucou
// 	}
// }

// Class B : public A
// {
// 	print {
// 		caca
// 	}
// }


// B b.
// b.print()

// A a;
// a.print()

// A *a = new B()
// A *B = new A()



// a->print();


#endif