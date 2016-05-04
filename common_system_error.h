#ifndef SYSTEMERROR_H
#define SYSTEMERROR_H

#include <string>
#include <exception>

class SystemError: std::exception{
    public:
        SystemError(std::string &message, const std::string &file, int line);
        const char* what() const throw();
        virtual ~SystemError() throw();
    protected:
    private:
        std::string error_msg;
};

#endif // SYSTEMERROR_H
