/**
 * @file Bencoder.cpp
 * @author Andrej Klocok (xkloco00@vutbr.cz)
 * @version 1.0
 * @date 2019-04-28
 */

#include "Bencoder.h"

Bencoder::Bencoder(/* args */){}

Bencoder::~Bencoder(){}
/**
 * @brief Method bencodes JSON object to string representation
 * 
 * @param bencJson      json object
 * @return std::string  bencoded data
 */
std::string Bencoder::encode(json bencJson){
    std::string encodedString;  //bencoded string
    std::string valStr;         //temp val
    bool isDict = false;        //format of json object dict/list

    //according to object set flags
    if(bencJson.is_array()){
        encodedString = "l";
    } 
    else{
        encodedString = "d";
        isDict = true;
    }

    //according to algorithm for each key,value in json
    for (auto& [key, value] : bencJson.items()) {    
        //json as dictionary has key and value, as arr there are only values
        if(isDict)
            //string => len(key):key
            encodedString += std::to_string(key.length()) +":"+key;
        
        //number42 =>i42e
        if(value.is_number() ){    
            encodedString+="i"+value.dump()+"e";
        }
        //array [...] =>l...e
        else if (value.is_array())
        {
            encodedString += encode(value);
        }
        //dict {...} => d...e
        else if (value.is_object())
        {   
            encodedString += encode(value);
        }
        // :null( correct repr is {} ) => de
        else if (value.is_null())
        {
            encodedString += "de";
        }
        //string => len(value):value
        else{
            //get string
            valStr = value.dump();
            //erase " "
            valStr.erase(std::remove(valStr.begin(), valStr.end(), '\"'), valStr.end());
            //append to string
            encodedString += std::to_string(valStr.length()) +":"+valStr;
        }
    }
    
    //ending dictionary
    encodedString += "e";

    return encodedString;
}
/**
 * @brief Method debencodes from string representation to json object
 * 
 * @param bencodeString     bencoded string
 * @return json             representing json object
 */
json Bencoder::decode(std::string bencodeString){
    //output
    json decodedJson;
    //set class attribute
    this->iter = 1;


    //switch first char
    switch (bencodeString.at(0)){
        case 'd':
            //is dictionary
            decodedJson = this->decodeObj(bencodeString, true);
            break;
        case 'l':
            //is list
            decodedJson = this->decodeObj(bencodeString, false);     
            break;

        default:
            //parseErr
            throw BencodeExc();
            break;
    }
    
    return decodedJson;
}
/**
 * @brief Decode int representation f.e. "i42e" => "42"
 * 
 * @param bencodeString     bencoded string
 * @return std::string      integer in string or empty(error)
 */
std::string Bencoder::decodeInt(std::string bencodeString){
    //buffer
    std::string numberStr;

    //loop over chars
    for (; this->iter < (int) bencodeString.length(); this->iter++){
        switch (bencodeString.at(this->iter)){
            //end of integer
            case 'e':
                return numberStr;
            //numbs
            case '0':
            case '1':
            case '2':
            case '3':
            case '4':
            case '5':
            case '6':
            case '7':
            case '8':
            case '9':
                //append to buffer
                numberStr += bencodeString.at(this->iter);
                break;
            default:
                //parseErr
                throw BencodeExc();
                break;
        } 
    }
    //e was not found in the end nor number -> wrong format
    throw BencodeExc();
    return "";
}
/**
 * @brief Method decodes string from bencoded string
 * 
 * @param bencodeString     bencoded string
 * @return std::string      string or empty(err)
 */
std::string Bencoder::decodeString(std::string bencodeString){
    //buffer
    std::string numberBuf;
    //length of string
    int stringLen = 0;
    std::string tmpVal = "";
    
    for (; this->iter < (int) bencodeString.length(); this->iter++){
        switch (bencodeString.at(this->iter)){
            case '0':
            case '1':
            case '2':
            case '3':
            case '4':
            case '5':
            case '6':
            case '7':
            case '8':
            case '9':
                //get length
                numberBuf += bencodeString.at(this->iter);
                break;
            case ':':
                stringLen = std::stoi(numberBuf);
                //copy substring with given length
                tmpVal = bencodeString.substr(this->iter +1, stringLen);
                //shift iter
                this->iter += stringLen;
                return tmpVal;
            default:
                //parseErr
                throw BencodeExc();
                break;
        }
    }
    //bad format of bencoded data
    throw BencodeExc();
    return "";
}
/**
 * @brief Debencode of json object (dict/list)
 * 
 * @param bencodeString     bencoded string
 * @param isDict            boolean flag
 * @return json             json object
 */
json Bencoder::decodeObj(std::string bencodeString, bool isDict){
    json decodedJson;

    std::string keyBuff;
    bool hasKey = false;
    bool hasJson = false;
    bool hasNumber = false;

    for (; this->iter < (int) bencodeString.length(); this->iter++){
        std::string tmpVal = "";
        json tmpJson;
        switch (bencodeString.at(this->iter)){
            case 'd':
                this->iter++;   // so the iterator would point at next char
                tmpJson = this->decodeObj(bencodeString, true);
                hasJson = true;
                break;
            case 'l':
                this->iter++;   // so the iterator would point at next char
                tmpJson = this->decodeObj(bencodeString, false);
                hasJson = true;
                break;

            case 'i':
                this->iter++;   // so the iterator would point at next char
                //if val is empty -> error
                tmpVal = this->decodeInt(bencodeString);
                hasNumber = true;
                break;

            case 'e':
                return decodedJson;
        
            case '0':
            case '1':
            case '2':
            case '3':
            case '4':
            case '5':
            case '6':
            case '7':
            case '8':
            case '9':
                //if val is empty -> error
                tmpVal = this->decodeString(bencodeString);
                break;
            default:
                //parse error
                throw BencodeExc();
                break;
        }
        //can use explicit cast in JSON object
        if(isDict){
            //add key, value to JSON
            if(hasKey){
                if(hasJson){
                    decodedJson[keyBuff] = tmpJson;
                    hasJson = false;
                }
                else if (hasNumber)
                {
                    decodedJson[keyBuff] = std::stoi(tmpVal);
                    hasNumber = false;
                }
                else{
                    decodedJson[keyBuff] = tmpVal;
                }
            }
            else{
                keyBuff = tmpVal;
            }
            hasKey = !hasKey;
        }
        else{
            if(hasJson){
                decodedJson.push_back(tmpJson);
                hasJson = false;
            }
            else if (hasNumber)
            {
                decodedJson.push_back(std::stoi(tmpVal));
                hasNumber = false;
            }
            else{
                decodedJson.push_back(tmpVal);
            }
        }
        
    }
    //parse error
    throw BencodeExc();
    return decodedJson;
}