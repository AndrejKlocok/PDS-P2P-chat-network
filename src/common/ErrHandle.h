/**
 * @file ErrHandle.h
 * @author Andrej Klocok (xkloco00@vutbr.cz)
 * @version 1.0
 * @date 2019-04-28
 * 
 */
#ifndef ERRHANDLE_H
#define ERRHANDLE_H

#include <stdio.h>
#include <string>

enum class ErrCodes {WrongArg, UnknownCmd, ParseBencodedStringErr };

/**
 * @brief Error handler
 * 
 */
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