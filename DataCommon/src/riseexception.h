#ifndef RISEEXCEPTION_H
#define RISEEXCEPTION_H

#include <stdexcept>

class RiseException : public std::exception
{
public:
    RiseException(std::string message);
    char * what() {
        return this->msg.data();
    };
protected:
    std::string msg;
};

#endif // RISEEXCEPTION_H
