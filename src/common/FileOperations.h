/**
 * @file FileOperations.h
 * @author Andrej Klocok (xkloco00@vutbr.cz)
 * @version 1.0
 * @date 2019-04-28
 * 
 */
#ifndef FILEOPERATIONS_H
#include <map>
#include <sstream>
#include <fstream>
#include <string>

#include "MyExceptions.h"

std::map<std::string, std::string> readConfig(std::string config);

#endif // !FILEOPERATIONS_H