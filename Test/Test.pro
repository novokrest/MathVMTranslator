TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

LIBS += $$QMAKE_LIBS_DYNLOAD -LMyLibrary #-ldl

INCLUDEPATH += /home/novokrest/Github/MathVMTranslator/libs/asmjit/src

SOURCES += main.cpp \
    ../libs/asmjit/src/asmjit/base/assembler.cpp \
    ../libs/asmjit/src/asmjit/base/codegen.cpp \
    ../libs/asmjit/src/asmjit/base/compiler.cpp \
    ../libs/asmjit/src/asmjit/base/constpool.cpp \
    ../libs/asmjit/src/asmjit/base/containers.cpp \
    ../libs/asmjit/src/asmjit/base/context.cpp \
    ../libs/asmjit/src/asmjit/base/cpuinfo.cpp \
    ../libs/asmjit/src/asmjit/base/cputicks.cpp \
    ../libs/asmjit/src/asmjit/base/error.cpp \
    ../libs/asmjit/src/asmjit/base/globals.cpp \
    ../libs/asmjit/src/asmjit/base/intutil.cpp \
    ../libs/asmjit/src/asmjit/base/logger.cpp \
    ../libs/asmjit/src/asmjit/base/operand.cpp \
    ../libs/asmjit/src/asmjit/base/runtime.cpp \
    ../libs/asmjit/src/asmjit/base/string.cpp \
    ../libs/asmjit/src/asmjit/base/vmem.cpp \
    ../libs/asmjit/src/asmjit/base/zone.cpp \
    ../libs/asmjit/src/asmjit/x86/x86assembler.cpp \
    ../libs/asmjit/src/asmjit/x86/x86compiler.cpp \
    ../libs/asmjit/src/asmjit/x86/x86context.cpp \
    ../libs/asmjit/src/asmjit/x86/x86cpuinfo.cpp \
    ../libs/asmjit/src/asmjit/x86/x86inst.cpp \
    ../libs/asmjit/src/asmjit/x86/x86operand_regs.cpp \
    ../libs/asmjit/src/asmjit/x86/x86operand.cpp \
    ../libs/asmjit/src/asmjit/x86/x86scheduler.cpp

OTHER_FILES += \


HEADERS += \
    ../libs/asmjit/src/asmjit/base/assembler.h \
    ../libs/asmjit/src/asmjit/base/codegen.h \
    ../libs/asmjit/src/asmjit/base/compiler.h \
    ../libs/asmjit/src/asmjit/base/constpool.h \
    ../libs/asmjit/src/asmjit/base/containers.h \
    ../libs/asmjit/src/asmjit/base/context_p.h \
    ../libs/asmjit/src/asmjit/base/cpuinfo.h \
    ../libs/asmjit/src/asmjit/base/cputicks.h \
    ../libs/asmjit/src/asmjit/base/error.h \
    ../libs/asmjit/src/asmjit/base/globals.h \
    ../libs/asmjit/src/asmjit/base/intutil.h \
    ../libs/asmjit/src/asmjit/base/lock.h \
    ../libs/asmjit/src/asmjit/base/logger.h \
    ../libs/asmjit/src/asmjit/base/operand.h \
    ../libs/asmjit/src/asmjit/base/runtime.h \
    ../libs/asmjit/src/asmjit/base/string.h \
    ../libs/asmjit/src/asmjit/base/vectypes.h \
    ../libs/asmjit/src/asmjit/base/vmem.h \
    ../libs/asmjit/src/asmjit/base/zone.h \
    ../libs/asmjit/src/asmjit/apibegin.h \
    ../libs/asmjit/src/asmjit/apiend.h \
    ../libs/asmjit/src/asmjit/asmjit.h \
    ../libs/asmjit/src/asmjit/base.h \
    ../libs/asmjit/src/asmjit/build.h \
    ../libs/asmjit/src/asmjit/config.h \
    ../libs/asmjit/src/asmjit/host.h \
    ../libs/asmjit/src/asmjit/x86.h \
    ../libs/asmjit/src/asmjit/x86/x86assembler.h \
    ../libs/asmjit/src/asmjit/x86/x86compiler.h \
    ../libs/asmjit/src/asmjit/x86/x86context_p.h \
    ../libs/asmjit/src/asmjit/x86/x86cpuinfo.h \
    ../libs/asmjit/src/asmjit/x86/x86inst.h \
    ../libs/asmjit/src/asmjit/x86/x86operand.h \
    ../libs/asmjit/src/asmjit/x86/x86scheduler_p.h \
    union_test.h


