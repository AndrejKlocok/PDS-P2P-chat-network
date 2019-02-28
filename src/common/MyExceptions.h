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

struct SocketExc : public std::exception
{
	const char * what () const throw ()
    {
    	return "Exception raised during Socket creation";
    }
};

struct SocketBindExc : public std::exception
{
	const char * what () const throw ()
    {
    	return "Exception raised during Socket binding";
    }
};

struct SocketOptionExc : public std::exception
{
	const char * what () const throw ()
    {
    	return "Exception raised during setsockopt";
    }
};

struct SocketDataExc : public std::exception
{
	const char * what () const throw ()
    {
    	return "Exception raised recvFrom -1";
    }
};
#endif // !MYEXCEPTIONS_H