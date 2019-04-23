#ifndef FILEOPERATIONS_H
#include <map>
#include <sstream>
#include <fstream>
#include <string>

#include "MyExceptions.h"

std::map<std::string, std::string> readConfig(std::string config);

#endif // !FILEOPERATIONS_H