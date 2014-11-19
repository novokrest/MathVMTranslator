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
    vm/translator.cpp \
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
    2/BytecodeGenerator.cpp \
    2/TypeInferencer.cpp \
    students/2014/novokreschenov/1/ast_printer.cpp

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
#    2/BytecodeGenerator.h \
#    2/TypeInferencer.h \
    students/2014/novokreschenov/1/ast_printer.h

INCLUDEPATH += vm \
               include \
               libs/AsmJit

OTHER_FILES += \
    libs/AsmJit/README.txt \
    README.txt \
    test_function.mvm
