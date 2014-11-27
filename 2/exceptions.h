#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

#include <cstring>
#include <exception>

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
public:
    InterpretationException() {
    }

    InterpretationException(string const& message)
        : MessageException(message) {
    }

    virtual ~InterpretationException() throw() {
    }
};

#endif // EXCEPTIONS_H
