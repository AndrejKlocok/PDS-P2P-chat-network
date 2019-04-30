/**
 * @file FileOperations.cpp
 * @author Andrej Klocok (xkloco00@vutbr.cz)
 * @version 1.0
 * @date 2019-04-28
 * 
 */
#include "FileOperations.h"

/**
 * @brief Function reads config file and creates map structure
 * 
 * @param config path to config file
 * @return std::map<std::string, std::string> 
 */
std::map<std::string, std::string> readConfig(std::string config){
        std::ifstream file(config);
        std::map<std::string, std::string> configMap;
        // check if file exists
        if (file.is_open()) {
            std::string line, name, value;
            // read line
            while (std::getline(file, line))
            {
                // structure of file is "key value"
                std::istringstream iss(line);
                if (!(iss >> name >> value)) { 
                    throw LocalException("Wrong config file structure: f.e. \"ThreadPoolServer 100\""); 
                }
                configMap[name] = value;
            }
            file.close();
        }
    return configMap;
}