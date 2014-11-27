#############################################################################
# Makefile for building: MathVMTranslator
# Generated by qmake (3.0) (Qt 5.2.1)
# Project:  MathVMTranslator.pro
# Template: app
# Command: /usr/lib/x86_64-linux-gnu/qt5/bin/qmake -spec linux-g++-64 CONFIG+=debug CONFIG+=declarative_debug CONFIG+=qml_debug -o Makefile MathVMTranslator.pro
#############################################################################

MAKEFILE      = Makefile

####### Compiler, tools and options

CC            = gcc
CXX           = g++
DEFINES       = -DQT_QML_DEBUG -DQT_DECLARATIVE_DEBUG
CFLAGS        = -m64 -pipe -g -Wall -W -fPIE $(DEFINES)
CXXFLAGS      = -m64 -pipe -g -Wall -W -fPIE $(DEFINES)
INCPATH       = -I/usr/lib/x86_64-linux-gnu/qt5/mkspecs/linux-g++-64 -I. -Ivm -Iinclude -Ilibs/AsmJit -I2
LINK          = g++
LFLAGS        = -m64
LIBS          = $(SUBLIBS)  
AR            = ar cqs
RANLIB        = 
QMAKE         = /usr/lib/x86_64-linux-gnu/qt5/bin/qmake
TAR           = tar -cf
COMPRESS      = gzip -9f
COPY          = cp -f
SED           = sed
COPY_FILE     = cp -f
COPY_DIR      = cp -f -R
STRIP         = strip
INSTALL_FILE  = install -m 644 -p
INSTALL_DIR   = $(COPY_DIR)
INSTALL_PROGRAM = install -m 755 -p
DEL_FILE      = rm -f
SYMLINK       = ln -f -s
DEL_DIR       = rmdir
MOVE          = mv -f
CHK_DIR_EXISTS= test -d
MKDIR         = mkdir -p

####### Output directory

OBJECTS_DIR   = ./

####### Files

SOURCES       = main.cpp \
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
		2/bytecodegenerator.cpp \
		2/typeinferencer.cpp \
		2/interpretercode.cpp \
		2/contextmanager.cpp 
OBJECTS       = main.o \
		ast.o \
		interpreter.o \
		mathvm.o \
		parser.o \
		scanner.o \
		translator.o \
		utils.o \
		Assembler.o \
		AssemblerX86X64.o \
		CodeGenerator.o \
		Compiler.o \
		CompilerX86X64.o \
		CpuInfo.o \
		Defs.o \
		DefsX86X64.o \
		Logger.o \
		MemoryManager.o \
		Operand.o \
		OperandX86X64.o \
		Platform.o \
		Util.o \
		bytecodegenerator.o \
		typeinferencer.o \
		interpretercode.o \
		contextmanager.o
DIST          = /usr/lib/x86_64-linux-gnu/qt5/mkspecs/features/spec_pre.prf \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/common/shell-unix.conf \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/common/unix.conf \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/common/linux.conf \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/common/gcc-base.conf \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/common/gcc-base-unix.conf \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/common/g++-base.conf \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/common/g++-unix.conf \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/qconfig.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_bootstrap_private.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_concurrent.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_concurrent_private.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_core.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_core_private.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_dbus.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_dbus_private.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_gui.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_gui_private.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_network.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_network_private.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_opengl.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_opengl_private.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_openglextensions.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_openglextensions_private.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_platformsupport_private.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_printsupport.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_printsupport_private.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_qml.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_qmltest.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_quick.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_sql.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_sql_private.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_testlib.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_testlib_private.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_widgets.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_widgets_private.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_xml.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_xml_private.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/features/qt_functions.prf \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/features/qt_config.prf \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/linux-g++-64/qmake.conf \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/features/spec_post.prf \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/features/exclusive_builds.prf \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/features/default_pre.prf \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/features/resolve_config.prf \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/features/default_post.prf \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/features/qml_debug.prf \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/features/declarative_debug.prf \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/features/unix/gdb_dwarf_index.prf \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/features/warn_on.prf \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/features/testcase_targets.prf \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/features/exceptions.prf \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/features/yacc.prf \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/features/lex.prf \
		MathVMTranslator.pro \
		MathVMTranslator.pro
QMAKE_TARGET  = MathVMTranslator
DESTDIR       = #avoid trailing-slash linebreak
TARGET        = MathVMTranslator


first: all
####### Implicit rules

.SUFFIXES: .o .c .cpp .cc .cxx .C

.cpp.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

.cc.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

.cxx.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

.C.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

.c.o:
	$(CC) -c $(CFLAGS) $(INCPATH) -o "$@" "$<"

####### Build rules

all: Makefile $(TARGET)

$(TARGET):  $(OBJECTS)  
	$(LINK) $(LFLAGS) -o $(TARGET) $(OBJECTS) $(OBJCOMP) $(LIBS)
	{ test -n "$(DESTDIR)" && DESTDIR="$(DESTDIR)" || DESTDIR=.; } && test $$(gdb --version | sed -e 's,[^0-9][^0-9]*\([0-9]\)\.\([0-9]\).*,\1\2,;q') -gt 72 && gdb --nx --batch --quiet -ex 'set confirm off' -ex "save gdb-index $$DESTDIR" -ex quit '$(TARGET)' && test -f $(TARGET).gdb-index && objcopy --add-section '.gdb_index=$(TARGET).gdb-index' --set-section-flags '.gdb_index=readonly' '$(TARGET)' '$(TARGET)' && rm -f $(TARGET).gdb-index || true

Makefile: MathVMTranslator.pro /usr/lib/x86_64-linux-gnu/qt5/mkspecs/linux-g++-64/qmake.conf /usr/lib/x86_64-linux-gnu/qt5/mkspecs/features/spec_pre.prf \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/common/shell-unix.conf \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/common/unix.conf \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/common/linux.conf \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/common/gcc-base.conf \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/common/gcc-base-unix.conf \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/common/g++-base.conf \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/common/g++-unix.conf \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/qconfig.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_bootstrap_private.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_concurrent.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_concurrent_private.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_core.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_core_private.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_dbus.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_dbus_private.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_gui.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_gui_private.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_network.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_network_private.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_opengl.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_opengl_private.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_openglextensions.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_openglextensions_private.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_platformsupport_private.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_printsupport.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_printsupport_private.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_qml.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_qmltest.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_quick.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_sql.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_sql_private.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_testlib.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_testlib_private.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_widgets.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_widgets_private.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_xml.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_xml_private.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/features/qt_functions.prf \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/features/qt_config.prf \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/linux-g++-64/qmake.conf \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/features/spec_post.prf \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/features/exclusive_builds.prf \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/features/default_pre.prf \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/features/resolve_config.prf \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/features/default_post.prf \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/features/qml_debug.prf \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/features/declarative_debug.prf \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/features/unix/gdb_dwarf_index.prf \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/features/warn_on.prf \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/features/testcase_targets.prf \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/features/exceptions.prf \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/features/yacc.prf \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/features/lex.prf \
		MathVMTranslator.pro
	$(QMAKE) -spec linux-g++-64 CONFIG+=debug CONFIG+=declarative_debug CONFIG+=qml_debug -o Makefile MathVMTranslator.pro
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/features/spec_pre.prf:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/common/shell-unix.conf:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/common/unix.conf:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/common/linux.conf:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/common/gcc-base.conf:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/common/gcc-base-unix.conf:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/common/g++-base.conf:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/common/g++-unix.conf:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/qconfig.pri:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_bootstrap_private.pri:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_concurrent.pri:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_concurrent_private.pri:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_core.pri:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_core_private.pri:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_dbus.pri:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_dbus_private.pri:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_gui.pri:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_gui_private.pri:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_network.pri:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_network_private.pri:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_opengl.pri:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_opengl_private.pri:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_openglextensions.pri:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_openglextensions_private.pri:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_platformsupport_private.pri:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_printsupport.pri:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_printsupport_private.pri:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_qml.pri:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_qmltest.pri:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_quick.pri:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_sql.pri:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_sql_private.pri:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_testlib.pri:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_testlib_private.pri:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_widgets.pri:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_widgets_private.pri:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_xml.pri:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_xml_private.pri:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/features/qt_functions.prf:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/features/qt_config.prf:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/linux-g++-64/qmake.conf:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/features/spec_post.prf:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/features/exclusive_builds.prf:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/features/default_pre.prf:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/features/resolve_config.prf:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/features/default_post.prf:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/features/qml_debug.prf:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/features/declarative_debug.prf:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/features/unix/gdb_dwarf_index.prf:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/features/warn_on.prf:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/features/testcase_targets.prf:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/features/exceptions.prf:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/features/yacc.prf:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/features/lex.prf:
MathVMTranslator.pro:
qmake: FORCE
	@$(QMAKE) -spec linux-g++-64 CONFIG+=debug CONFIG+=declarative_debug CONFIG+=qml_debug -o Makefile MathVMTranslator.pro

qmake_all: FORCE

dist: 
	@test -d .tmp/MathVMTranslator1.0.0 || mkdir -p .tmp/MathVMTranslator1.0.0
	$(COPY_FILE) --parents $(SOURCES) $(DIST) .tmp/MathVMTranslator1.0.0/ && (cd `dirname .tmp/MathVMTranslator1.0.0` && $(TAR) MathVMTranslator1.0.0.tar MathVMTranslator1.0.0 && $(COMPRESS) MathVMTranslator1.0.0.tar) && $(MOVE) `dirname .tmp/MathVMTranslator1.0.0`/MathVMTranslator1.0.0.tar.gz . && $(DEL_FILE) -r .tmp/MathVMTranslator1.0.0


clean:compiler_clean 
	-$(DEL_FILE) $(OBJECTS)
	-$(DEL_FILE) *~ core *.core


####### Sub-libraries

distclean: clean
	-$(DEL_FILE) $(TARGET) 
	-$(DEL_FILE) Makefile


check: first

compiler_yacc_decl_make_all:
compiler_yacc_decl_clean:
compiler_yacc_impl_make_all:
compiler_yacc_impl_clean:
compiler_lex_make_all:
compiler_lex_clean:
compiler_clean: 

####### Compile

main.o: main.cpp include/mathvm.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o main.o main.cpp

ast.o: vm/ast.cpp include/ast.h \
		include/mathvm.h \
		include/visitors.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o ast.o vm/ast.cpp

interpreter.o: vm/interpreter.cpp include/mathvm.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o interpreter.o vm/interpreter.cpp

mathvm.o: vm/mathvm.cpp include/mathvm.h \
		include/ast.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o mathvm.o vm/mathvm.cpp

parser.o: vm/parser.cpp include/ast.h \
		include/mathvm.h \
		vm/parser.h \
		vm/scanner.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o parser.o vm/parser.cpp

scanner.o: vm/scanner.cpp include/mathvm.h \
		vm/scanner.h \
		include/ast.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o scanner.o vm/scanner.cpp

translator.o: vm/translator.cpp include/mathvm.h \
		vm/parser.h \
		include/ast.h \
		vm/scanner.h \
		include/visitors.h \
		2/bytecodegenerator.h \
		2/interpretercode.h \
		2/contextmanager.h \
		2/exceptions.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o translator.o vm/translator.cpp

utils.o: vm/utils.cpp include/mathvm.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o utils.o vm/utils.cpp

Assembler.o: libs/AsmJit/Assembler.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o Assembler.o libs/AsmJit/Assembler.cpp

AssemblerX86X64.o: libs/AsmJit/AssemblerX86X64.cpp libs/AsmJit/Assembler.h \
		libs/AsmJit/Build.h \
		libs/AsmJit/Config.h \
		libs/AsmJit/AssemblerX86X64.h \
		libs/AsmJit/Defs.h \
		libs/AsmJit/DefsX86X64.h \
		libs/AsmJit/Util.h \
		libs/AsmJit/ApiBegin.h \
		libs/AsmJit/ApiEnd.h \
		libs/AsmJit/Operand.h \
		libs/AsmJit/OperandX86X64.h \
		libs/AsmJit/CodeGenerator.h \
		libs/AsmJit/CpuInfo.h \
		libs/AsmJit/Logger.h \
		libs/AsmJit/MemoryManager.h \
		libs/AsmJit/Platform.h \
		libs/AsmJit/Util_p.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o AssemblerX86X64.o libs/AsmJit/AssemblerX86X64.cpp

CodeGenerator.o: libs/AsmJit/CodeGenerator.cpp libs/AsmJit/Assembler.h \
		libs/AsmJit/Build.h \
		libs/AsmJit/Config.h \
		libs/AsmJit/AssemblerX86X64.h \
		libs/AsmJit/Defs.h \
		libs/AsmJit/DefsX86X64.h \
		libs/AsmJit/Util.h \
		libs/AsmJit/ApiBegin.h \
		libs/AsmJit/ApiEnd.h \
		libs/AsmJit/Operand.h \
		libs/AsmJit/OperandX86X64.h \
		libs/AsmJit/CodeGenerator.h \
		libs/AsmJit/MemoryManager.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o CodeGenerator.o libs/AsmJit/CodeGenerator.cpp

Compiler.o: libs/AsmJit/Compiler.cpp libs/AsmJit/Assembler.h \
		libs/AsmJit/Build.h \
		libs/AsmJit/Config.h \
		libs/AsmJit/AssemblerX86X64.h \
		libs/AsmJit/Defs.h \
		libs/AsmJit/DefsX86X64.h \
		libs/AsmJit/Util.h \
		libs/AsmJit/ApiBegin.h \
		libs/AsmJit/ApiEnd.h \
		libs/AsmJit/Operand.h \
		libs/AsmJit/OperandX86X64.h \
		libs/AsmJit/Compiler.h \
		libs/AsmJit/CompilerX86X64.h \
		libs/AsmJit/CpuInfo.h \
		libs/AsmJit/Logger.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o Compiler.o libs/AsmJit/Compiler.cpp

CompilerX86X64.o: libs/AsmJit/CompilerX86X64.cpp libs/AsmJit/Assembler.h \
		libs/AsmJit/Build.h \
		libs/AsmJit/Config.h \
		libs/AsmJit/AssemblerX86X64.h \
		libs/AsmJit/Defs.h \
		libs/AsmJit/DefsX86X64.h \
		libs/AsmJit/Util.h \
		libs/AsmJit/ApiBegin.h \
		libs/AsmJit/ApiEnd.h \
		libs/AsmJit/Operand.h \
		libs/AsmJit/OperandX86X64.h \
		libs/AsmJit/CodeGenerator.h \
		libs/AsmJit/Compiler.h \
		libs/AsmJit/CompilerX86X64.h \
		libs/AsmJit/CpuInfo.h \
		libs/AsmJit/Logger.h \
		libs/AsmJit/Util_p.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o CompilerX86X64.o libs/AsmJit/CompilerX86X64.cpp

CpuInfo.o: libs/AsmJit/CpuInfo.cpp libs/AsmJit/CpuInfo.h \
		libs/AsmJit/Build.h \
		libs/AsmJit/Config.h \
		libs/AsmJit/ApiBegin.h \
		libs/AsmJit/ApiEnd.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o CpuInfo.o libs/AsmJit/CpuInfo.cpp

Defs.o: libs/AsmJit/Defs.cpp libs/AsmJit/Defs.h \
		libs/AsmJit/Build.h \
		libs/AsmJit/Config.h \
		libs/AsmJit/DefsX86X64.h \
		libs/AsmJit/Util.h \
		libs/AsmJit/ApiBegin.h \
		libs/AsmJit/ApiEnd.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o Defs.o libs/AsmJit/Defs.cpp

DefsX86X64.o: libs/AsmJit/DefsX86X64.cpp libs/AsmJit/Defs.h \
		libs/AsmJit/Build.h \
		libs/AsmJit/Config.h \
		libs/AsmJit/DefsX86X64.h \
		libs/AsmJit/Util.h \
		libs/AsmJit/ApiBegin.h \
		libs/AsmJit/ApiEnd.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o DefsX86X64.o libs/AsmJit/DefsX86X64.cpp

Logger.o: libs/AsmJit/Logger.cpp libs/AsmJit/Logger.h \
		libs/AsmJit/Defs.h \
		libs/AsmJit/Build.h \
		libs/AsmJit/Config.h \
		libs/AsmJit/DefsX86X64.h \
		libs/AsmJit/Util.h \
		libs/AsmJit/ApiBegin.h \
		libs/AsmJit/ApiEnd.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o Logger.o libs/AsmJit/Logger.cpp

MemoryManager.o: libs/AsmJit/MemoryManager.cpp libs/AsmJit/Build.h \
		libs/AsmJit/Config.h \
		libs/AsmJit/MemoryManager.h \
		libs/AsmJit/Defs.h \
		libs/AsmJit/DefsX86X64.h \
		libs/AsmJit/Util.h \
		libs/AsmJit/ApiBegin.h \
		libs/AsmJit/ApiEnd.h \
		libs/AsmJit/Platform.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o MemoryManager.o libs/AsmJit/MemoryManager.cpp

Operand.o: libs/AsmJit/Operand.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o Operand.o libs/AsmJit/Operand.cpp

OperandX86X64.o: libs/AsmJit/OperandX86X64.cpp libs/AsmJit/Defs.h \
		libs/AsmJit/Build.h \
		libs/AsmJit/Config.h \
		libs/AsmJit/DefsX86X64.h \
		libs/AsmJit/Util.h \
		libs/AsmJit/ApiBegin.h \
		libs/AsmJit/ApiEnd.h \
		libs/AsmJit/Operand.h \
		libs/AsmJit/OperandX86X64.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o OperandX86X64.o libs/AsmJit/OperandX86X64.cpp

Platform.o: libs/AsmJit/Platform.cpp libs/AsmJit/Platform.h \
		libs/AsmJit/Build.h \
		libs/AsmJit/Config.h \
		libs/AsmJit/ApiBegin.h \
		libs/AsmJit/ApiEnd.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o Platform.o libs/AsmJit/Platform.cpp

Util.o: libs/AsmJit/Util.cpp libs/AsmJit/Build.h \
		libs/AsmJit/Config.h \
		libs/AsmJit/Util_p.h \
		libs/AsmJit/Util.h \
		libs/AsmJit/ApiBegin.h \
		libs/AsmJit/ApiEnd.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o Util.o libs/AsmJit/Util.cpp

bytecodegenerator.o: 2/bytecodegenerator.cpp 2/bytecodegenerator.h \
		include/mathvm.h \
		include/visitors.h \
		include/ast.h \
		2/interpretercode.h \
		2/contextmanager.h \
		2/exceptions.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o bytecodegenerator.o 2/bytecodegenerator.cpp

typeinferencer.o: 2/typeinferencer.cpp 2/bytecodegenerator.h \
		include/mathvm.h \
		include/visitors.h \
		include/ast.h \
		2/interpretercode.h \
		2/contextmanager.h \
		2/exceptions.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o typeinferencer.o 2/typeinferencer.cpp

interpretercode.o: 2/interpretercode.cpp 2/interpretercode.h \
		include/mathvm.h \
		2/contextmanager.h \
		2/exceptions.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o interpretercode.o 2/interpretercode.cpp

contextmanager.o: 2/contextmanager.cpp 2/contextmanager.h \
		include/mathvm.h \
		2/exceptions.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o contextmanager.o 2/contextmanager.cpp

####### Install

install:   FORCE

uninstall:   FORCE

FORCE:

