#include "common_system_error.h"
#include <sstream>
#include <stdexcept>

SystemError::SystemError(std::string &message, const std::string &file, int line){
    std::stringstream msg;
    msg << "Error: " << message << " in file: " << file << " - line: " << line;
    msg << "\n";
    this->error_msg = msg.str();
}

const char* SystemError::what() const throw(){
    return this->error_msg.c_str();
}

SystemError::~SystemError() throw(){}
