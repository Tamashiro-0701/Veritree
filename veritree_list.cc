#include <iostream>
#include <fstream>
#include <regex>
#include <string>
void searchInstances(const std::string& filename) {
    std::ifstream file(filename); // open the file
    if (file.is_open()) {
        std::string line;
        std::regex instanceRegex(R"(^\s*([\w_]+)\s+([\w_]+)\s*\([^)]*\);)");
        while (std::getline(file, line)) { // read file
            std::smatch match;
            if (std::regex_search(line, match, instanceRegex)) { // if detect instance statment
                std::string moduleName = match[1].str(); // get module name
                std::string instanceName = match[2].str(); // get instance name
                // Parse instance statement
                std::cout << "module name: " << moduleName << std::endl;
                std::cout << "instance name: " << instanceName << std::endl;
                // Recurrently searches for lower-level module files
                std::string subModuleFilename = moduleName + ".sv"; 
                searchInstances(subModuleFilename);
            }
        }
        file.close(); // close the file
    } else {
        std::cout << "Can't open the" << std::endl;
    }
}
int main() {
    std::string topModuleFilename = "top_module.sv"; 
    searchInstances(topModuleFilename);
    return 0;
}
