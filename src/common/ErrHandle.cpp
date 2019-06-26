/**
 * @file ErrHandle.cpp
 * @author Andrej Klocok (xkloco00@vutbr.cz)
 * @version 1.0
 * @date 2019-04-28
 * 
 */
#include "ErrHandle.h"

ErrHandle::ErrHandle(/* args */){}

ErrHandle::~ErrHandle(){}

/**
 * @brief 
 * 
 * @param code  type of error
 * @param option bonus option
 */
void ErrHandle::printErrMessage(ErrCodes code, std::string option){
    //errcode
    switch (code)
    {
        case ErrCodes::WrongArg :
            fprintf(stderr, "Wrong arguments\n");
            break;

        case ErrCodes::UnknownCmd :
            fprintf(stderr, "Unknown --command %s \n", option.c_str());
            break;

        case ErrCodes::ParseBencodedStringErr :
            fprintf(stderr, "Error (Bdecode) in parsing: %s \n", option.c_str());
            break;
            
        default:
            break;
    }
}