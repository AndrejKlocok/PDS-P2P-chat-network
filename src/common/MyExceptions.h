#ifndef MYEXCEPTIONS_H
#define MYEXCEPTIONS_H

#include <iostream>
#include <exception>
#include <stdarg.h>

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

struct PeerMsgEmpty : public std::exception
{
	const char * what () const throw ()
    {
    	return "Exception raised: No messages to send";
    }
};

struct PeerNotFoundException : std::exception
{
    char text[1024];

    PeerNotFoundException(char const* fmt, ...) __attribute__((format(printf,2,3))) {
        va_list ap;
        va_start(ap, fmt);
        vsnprintf(text, sizeof text, fmt, ap);
        va_end(ap);
    }

    char const* what() const throw() { return text; }
};

struct CustomException : std::exception
{
    char text[1024];

    CustomException(char const* fmt, ...) __attribute__((format(printf,2,3))) {
        va_list ap;
        va_start(ap, fmt);
        vsnprintf(text, sizeof text, fmt, ap);
        va_end(ap);
    }

    char const* what() const throw() { return text; }
};

#endif // !MYEXCEPTIONS_H