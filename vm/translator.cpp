#include "mathvm.h"
#include "parser.h"
#include "visitors.h"

namespace mathvm {

// Implement me!
Translator* Translator::create(const string& impl) {
    if (impl == "" || impl == "intepreter") {
        return new BytecodeTranslatorImpl();
    }
    if (impl == "jit") {
        //return new MachCodeTranslatorImpl();
    }
    assert(false);
    return 0;
}

Status* BytecodeTranslatorImpl::translate(const string& program, Code* *code) {
    Parser parser;
    Status* status = parser.parseProgram(program);
    if (status != NULL && status->isError()) {
        return status;
    }

    AstFunction* top = parser.top();
    return Status::Ok();
}

Status* BytecodeTranslatorImpl::translateBytecode(const string &program, InterpreterCodeImpl **code)
{
    Parser parser;
    Status* status = parser.parseProgram(program);
    if (status != NULL && status->isError()) {
        return status;
    }

    AstFunction* top = parser.top();
    return 0;
}

}
