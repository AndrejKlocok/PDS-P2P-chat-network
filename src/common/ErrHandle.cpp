#include "ErrHandle.h"

ErrHandle::ErrHandle(/* args */)
{
}

ErrHandle::~ErrHandle()
{
}

void ErrHandle::printErrMessage(ErrCodes code, std::string option){
    
    switch (code)
    {
        case ErrCodes::WrongArg :
            fprintf(stderr, "Wrong arguments\n");
            break;

        case ErrCodes::UnknownCmd :
            fprintf(stderr, "Unknown --command %s \n", option.c_str());
        
        case ErrCodes::ParseBencodedStringErr :
            fprintf(stderr, "Error (Bdecode) in parsing: %s \n", option.c_str());

        default:
            break;
    }
}