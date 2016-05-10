#include "common_system_error.h"
#include <sstream>
#include <stdexcept>
#include <string>

SystemError::SystemError(std::string &e_msg, const std::string &file, int line){
    std::stringstream msg;
    msg << "Error: " << e_msg << " in file: " << file << " - line: " << line;
    msg << "\n";
    this->error_msg = msg.str();
}

const char* SystemError::what() const throw(){
    return this->error_msg.c_str();
}

SystemError::~SystemError() throw(){}
