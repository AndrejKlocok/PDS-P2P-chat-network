#include "FileOperations.h"

std::map<std::string, std::string> readConfig(std::string config){
        std::ifstream file(config);
        std::map<std::string, std::string> configMap;

        if (file.is_open()) {
            std::string line, name, value;
            while (std::getline(file, line))
            {
                std::istringstream iss(line);
                if (!(iss >> name >> value)) { 
                    throw LocalException("Wrong config file structure: f.e. \"ThreadPoolServer 100\""); 
                }
                configMap[name] = value;
            }
            file.close();
        }
        else
        {
            throw LocalException("Config file not found");
        }
    return configMap;
}