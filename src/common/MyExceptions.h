#ifndef MYEXCEPTIONS_H
#define MYEXCEPTIONS_H

#include <iostream>
#include <exception>

struct BencodeExc : public std::exception
{
	const char * what () const throw ()
    {
    	return "Bencoder parse error";
    }
};

#endif // !MYEXCEPTIONS_H