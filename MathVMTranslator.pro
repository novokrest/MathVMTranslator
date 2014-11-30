TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    vm/ast.cpp \
    vm/interpreter.cpp \
    vm/mathvm.cpp \
    vm/parser.cpp \
    vm/scanner.cpp \
#    vm/translator.cpp \
    vm/utils.cpp \
    libs/AsmJit/Assembler.cpp \
    libs/AsmJit/AssemblerX86X64.cpp \
    libs/AsmJit/CodeGenerator.cpp \
    libs/AsmJit/Compiler.cpp \
    libs/AsmJit/CompilerX86X64.cpp \
    libs/AsmJit/CpuInfo.cpp \
    libs/AsmJit/Defs.cpp \
    libs/AsmJit/DefsX86X64.cpp \
    libs/AsmJit/Logger.cpp \
    libs/AsmJit/MemoryManager.cpp \
    libs/AsmJit/Operand.cpp \
    libs/AsmJit/OperandX86X64.cpp \
    libs/AsmJit/Platform.cpp \
    libs/AsmJit/Util.cpp \
#    students/2014/novokreschenov/1/ast_printer.cpp
    2/bytecodegenerator.cpp \
    2/typeinferencer.cpp \
    2/interpretercode.cpp \
    2/contextmanager.cpp \
    2/functioncontext.cpp \
    2/translator.cpp

HEADERS += \
    vm/parser.h \
    vm/scanner.h \
    include/ast.h \
    include/mathvm.h \
    include/visitors.h \
    libs/AsmJit/AssemblerX86X64.h \
    libs/AsmJit/ApiBegin.h \
    libs/AsmJit/ApiEnd.h \
    libs/AsmJit/AsmJit.h \
    libs/AsmJit/Assembler.h \
    libs/AsmJit/Build.h \
    libs/AsmJit/CodeGenerator.h \
    libs/AsmJit/Compiler.h \
    libs/AsmJit/CompilerX86X64.h \
    libs/AsmJit/Config.h \
    libs/AsmJit/CpuInfo.h \
    libs/AsmJit/Defs.h \
    libs/AsmJit/DefsX86X64.h \
    libs/AsmJit/Logger.h \
    libs/AsmJit/MemoryManager.h \
    libs/AsmJit/Operand.h \
    libs/AsmJit/OperandX86X64.h \
    libs/AsmJit/Platform.h \
    libs/AsmJit/Util_p.h \
    libs/AsmJit/Util.h \
#    students/2014/novokreschenov/1/ast_printer.h \
    2/bytecodegenerator.h \
    2/interpretercode.h \
    2/contextmanager.h \
    2/exceptions.h

INCLUDEPATH += vm \
               include \
               libs/AsmJit \
               2

OTHER_FILES += \
    libs/AsmJit/README.txt \
    README.txt \
    test_function.mvm \
    tests/add.expect \
    tests/add.mvm \
    tests/assign.expect \
    tests/assign.mvm \
    tests/bitwise.expect \
    tests/bitwise.mvm \
    tests/div.expect \
    tests/div.mvm \
    tests/expr.expect \
    tests/expr.mvm \
    tests/for.expect \
    tests/for.mvm \
    tests/function.expect \
    tests/function.mvm \
    tests/if.expect \
    tests/if.mvm \
    tests/literal.expect \
    tests/literal.mvm \
    tests/mul.expect \
    tests/mul.mvm \
    tests/sub.expect \
    tests/sub.mvm \
    tests/var.mvm \
    tests/while.expect \
    tests/while.mvm \
    tests/run.py \
    tests/additional/3function.expect \
    tests/additional/ackermann_closure.expect \
    tests/additional/ackermann_closure.mvm \
    tests/additional/ackermann.expect \
    tests/additional/ackermann.mvm \
    tests/additional/casts.expect \
    tests/additional/casts.mvm \
    tests/additional/closure.mvm \
    tests/additional/complex.expect \
    tests/additional/complex.mvm \
    tests/additional/complex2.expect \
    tests/additional/complex2.mvm \
    tests/additional/fib_closure.expect \
    tests/additional/fib_closure.mvm \
    tests/additional/fib.expect \
    tests/additional/fib.mvm \
    tests/additional/function-call.expect \
    tests/additional/function-call.mvm \
    tests/additional/function-cast.expect \
    tests/additional/function-cast.mvm \
    tests/additional/function.expect \
    tests/additional/function.mvm \
    tests/additional/vars.expect \
    tests/additional/vars.mvm \
    tests/optional/function_native.expect \
    tests/optional/function_native.mvm \
    tests/optional/plot.mvm \
    tests/perf/lissajous.mvm \
    tests/perf/plot.mvm \
    tests/perf/prime.mvm
