#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

#include <cstring>
#include <exception>
#include "mathvm.h"

using std::string;


class MessageException : public std::exception
{
    string _message;

public:
    MessageException() {
    }

    MessageException(string const& message)
        : _message(message) {
    }

    virtual ~MessageException() throw() {
    }


    virtual const char* what() const throw() {
        return _message.c_str();
    }
};

class TranslationException: public MessageException
{
public:
    TranslationException() {
    }

    TranslationException(string const& message)
        : MessageException(message) {
    }

    virtual ~TranslationException() throw() {
    }
};

class InterpretationException: public MessageException
{
    uint32_t _position;

public:
    InterpretationException(uint32_t position = mathvm::VT_INVALID)
        : _position(position) {
    }

    InterpretationException(string const& message, uint32_t position = mathvm::VT_INVALID)
        : MessageException(message), _position(position) {
    }

    virtual ~InterpretationException() throw() {
    }

    uint32_t position() {
        return _position;
    }
};

#endif // EXCEPTIONS_H
