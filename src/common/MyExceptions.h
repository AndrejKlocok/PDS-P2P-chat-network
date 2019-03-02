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

struct UnknownType : public std::exception
{
	const char * what () const throw ()
    {
    	return "Exception raised: type of message not found";
    }
};

struct NodeWrongId : public std::exception
{
	const char * what () const throw ()
    {
    	return "Exception raised: txid";
    }
};

#endif // !MYEXCEPTIONS_H