#include "mathvm.h"
#include "parser.h"
#include "visitors.h"
#include "bytecodegenerator.h"
#include "interpretercode.h"

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
    InterpreterCodeImpl* interpreterCode;
    Status* status = translateBytecode(program, &interpreterCode);
    *code = interpreterCode;

    return status;
}

Status* BytecodeTranslatorImpl::translateBytecode(const string &program, InterpreterCodeImpl **code)
{
    Parser parser;
    Status* status = parser.parseProgram(program);
    if (status != NULL && status->isError()) {
        return status;
    }

    AstFunction* top = parser.top();
    BytecodeGenerator bytecodeGenerator;
    InterpreterCodeImpl* bytecode = bytecodeGenerator.makeBytecode(top);
    if (bytecode == NULL) {
        return Status::Error("");
    }
    *code = bytecode;

    return status;
}

}
