#ifndef ERRHANDLE_H
#define ERRHANDLE_H

#include <stdio.h>
#include <string>

enum class ErrCodes {WrongArg, UnknownCmd };


class ErrHandle
{
private:
    /* data */
public:
    ErrHandle(/* args */);
    ~ErrHandle();

    static void printErrMessage(ErrCodes err, std::string option);
};


#endif // !ERRHANDLE_H