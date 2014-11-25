#include <iostream>
#include "asmjit/base.h"
#include "asmjit/asmjit.h"
#include "asmjit/config.h"
#include "asmjit/base/vmem.h"

#include <stdlib.h>

//int abs(int x)

typedef int (*abs_type)(int);

using namespace std;
using namespace asmjit;
using namespace asmjit::x86;

class A
{};

#include <dlfcn.h>

void load_and_execute_abs() {
    JitRuntime runtime;
    X86Assembler a(&runtime);
    FileLogger logger(stdout);
    a.setLogger(&logger);

    std::string abs_name = "abs";
    void* f_abs = dlsym(RTLD_DEFAULT, abs_name.c_str());
    ((abs_type)f_abs)(1);


    a.push(ebp);
    a.mov(ebp, esp);
    a.push(-1);
    a.call(imm((uint64_t)f_abs));
    int res = eax.getData<int>();
}

void invoke_function_by_ptr(void* f_ptr)
{
    JitRuntime runtime;
    X86Assembler assembler(&runtime);
    FileLogger logger(stdout);
    assembler.setLogger(&logger);
//    assembler.call();

    X86Compiler c(&runtime);
    X86GpVar address(c.newGpVar(kVarTypeUInt64));
    c.mov( address, (uint64_t)f_ptr);
//    c.call(address);

    assembler.mov(eax, (uint64_t)&f_ptr);
    assembler.call(eax);
    assembler.make();
//    assembler.call(ptr(eax));
//    assembler.mov(eax, f_ptr);
//    assembler.call(imm((uint64_t)&f_ptr));
}


int tmain()
{
    void* handle = dlopen("./libMyLibrary.so", RTLD_LAZY);
    if (!handle) {
        cout << "Couldn't open library" << endl;
        return 1;
    }
    dlerror();
    typedef void (*hello_t)();
    void* hello = dlsym(handle, "hello");
    const char* dl_sym_error = dlerror();
    if (dl_sym_error) {
        cout << "Cannot load symbol: 'hello'" << endl;
        dlclose(handle);
    }
    //((hello_t)hello)();

    invoke_function_by_ptr(hello);


    dlclose(handle);

//    load_and_execute_abs();
//    abs_type f_abs = (abs_type) dlsym(RTLD_DEFAULT, "abs");
//    cout << f_abs(-1) << endl;


    return 0;
}

#include "union_test.h"
#include <cstdio>

int main()
{
    typedef std::vector<int> vint;
    typedef std::vector<vint> vvint;

    vvint vv;
    vv.push_back(vint());
    cout << vv.size() << endl;
    Stack stack;
    //uint32_t el = stack.getInt32();

    double d = 3.434252532;
    printf("%.3f\n", d);

    return 0;
}



