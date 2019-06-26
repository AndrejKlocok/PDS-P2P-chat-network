/**
 * @file Bencoder.h
 * @author Andrej Klocok (xkloco00@vutbr.cz)
 * @version 1.0
 * @date 2019-04-28
 * 
 */
#ifndef BENCODER_H
#define BENCODER_H

#include <string>
#include <iostream>

#include "../../libs/json.hpp"
#include "ErrHandle.h"
#include "MyExceptions.h"
using json = nlohmann::json;
/**
 * @brief Class is used as bencoder/debecoder of JSON format of json.hpp. Throws BencodeExc
 * 
 * 
 */
class Bencoder
{
private:
    /* data */
    int iter;

    json decodeObj(std::string bencodeString, bool isDict);
    std::string decodeInt(std::string bencodedString);
    std::string decodeString(std::string bencodedString);

public:
    Bencoder(/* args */);
    ~Bencoder();
    
    std::string encode(json bencJson);
    json decode(std::string bencodeString);
};

#endif // !BENCODER_H