#ifndef INTERPRETERCODE_H
#define INTERPRETERCODE_H

#include "mathvm.h"
#include "contextmanager.h"

namespace mathvm {

class InterpreterCodeImpl : public Code
{
    InterpreterStack _stack;
    ContextManager _contextManager;
    std::vector<Bytecode*> _bytecodes;
    std::vector<uint32_t> _indexes;

    void executeBytecode();
    void executeBytecodeInsn(Instruction insn);
    Bytecode* bytecode();
    void addNewBytecode(Bytecode* bytecode);
    void removeLastBytecode();

    uint32_t bytecodeIndex();
    void shiftBytecodeIndex(int32_t shift);
    void setBytecodeIndex(uint32_t index);

    static int32_t compare(double upper, double lower);
    static int32_t compare(int32_t upper, int32_t lower);

#define EXECUTE_INSN(b, d, l)         \
    void execute##b();

    FOR_BYTECODES(EXECUTE_INSN)
#undef EXECUTE_INSN

    void executeBytecodeFunction(BytecodeFunction* bcFunction);
    void executeNativeFunction(NativeFunctionDescriptor& native);

public:
    virtual ~InterpreterCodeImpl();

    virtual Status* execute(vector<Var *> &vars);
    virtual void disassemble(ostream& out = cout, FunctionFilter* filter = 0);
};

class MessageException : public exception
{
    string _message;

public:
    MessageException() {
    }

    virtual ~MessageException() throw() {
    }

    MessageException(string const& message)
        : _message(message) {
    }

    virtual const char* what() const throw() {
        return _message.c_str();
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
};

}

#endif // INTERPRETERCODE_H
