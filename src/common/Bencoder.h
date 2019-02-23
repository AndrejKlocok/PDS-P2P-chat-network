/**
 * @file Bencoder.h
 * @author Andrej Klocok (xkloco00@vurbr.cz)
 * @brief 
 * @version 0.1
 * @date 2019-02-23
 * 
 * @copyright Copyright (c) 2019
 * 
 */
#ifndef BENCODER_H
#define BENCODE_H

#include <string>
#include <iostream>

#include "common/json.hpp"
#include "common/ErrHandle.h"
#include "common/MyExceptions.h"
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