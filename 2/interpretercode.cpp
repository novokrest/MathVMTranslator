#include "interpretercode.h"
#include <cstdio>


namespace mathvm {

int32_t InterpreterCodeImpl::compare(double upper, double lower) {
    if (upper == lower) {
        return 0;
    }

    return upper > lower ? 1 : -1;
}

int32_t InterpreterCodeImpl::compare(int32_t upper, int32_t lower) {
    if (upper == lower) {
        return 0;
    }

    return upper > lower ? 1 : -1;
}

InterpreterCodeImpl::~InterpreterCodeImpl()
{}

Status* InterpreterCodeImpl::execute(vector<Var *> &vars)
{
    return Status::Error("not implemented");
}

void InterpreterCodeImpl::disassemble(ostream &out, FunctionFilter *filter)
{}

void InterpreterCodeImpl::executeBytecode() {
    while(bytecodeIndex() != executedBytecode()->length()) {
        executeBytecodeInsn(executedBytecode()->get(index()));
    }
}

void InterpreterCodeImpl::executeBytecodeInsn(Instruction insn) {
    switch(insn) {
#define CASE_INSN(b, d, l)         \
    case BC_##b:                   \
    execute##b();              \
    break;

    FOR_BYTECODES(CASE_INSN)
        #undef CASE_INSN

            default:
        throw InterpretationException();
    break;
    }
}

Bytecode* InterpreterCodeImpl::bytecode() {
    return _bytecodes.back();
}

void InterpreterCodeImpl::addNewBytecode(Bytecode *bytecode) {
    _bytecodes.push_back(bytecode);
    _indexes.push_back(0);
}

void InterpreterCodeImpl::removeLastBytecode() {
    _bytecodes.pop_back();
    _indexes.pop_back();
}

uint32_t InterpreterCodeImpl::bytecodeIndex() {
    return _indexes.back();
}

void InterpreterCodeImpl::shiftBytecodeIndex(int32_t shift) {
    _indexes.back() += shift;
}

void InterpreterCodeImpl::setBytecodeIndex(uint32_t index) {
    _indexes.back() = index;
}

void InterpreterCodeImpl::executeINVALID() {
    throw InterpretationException("Invalid instruction");
}

void InterpreterCodeImpl::executeDLOAD()
{
    shiftBytecodeIndex(+1);
    double d = bytecode()->getDouble(index());
    loadOnTOS(VT_DOUBLE, d);
    shiftBytecodeIndex(+1);
}

void InterpreterCodeImpl::executeILOAD()
{
    shiftBytecodeIndex(+1);
    int32_t i = bytecode()->getTyped<int32_t>(index());
    loadOnTOS(VT_INT, i);
    shiftBytecodeIndex(+1);
}

void InterpreterCodeImpl::executeSLOAD()
{
    shiftBytecodeIndex(+1);
    uint16_t id = bytecode()->getTyped<uint16_t>(index());
    loadOnTOS(VT_STRING, id);
    shiftBytecodeIndex(+1);
}

void InterpreterCodeImpl::executeDLOAD0()
{
    loadOnTOS(VT_DOUBLE, 0);
    shiftBytecodeIndex(+1);
}

void InterpreterCodeImpl::executeILOAD0()
{
    loadOnTOS(VT_INT, 0);
    shiftBytecodeIndex(+1);
}

void InterpreterCodeImpl::executeSLOAD0()
{
    loadOnTOS(VT_STRING, 0);
    shiftBytecodeIndex(+1);
}

void InterpreterCodeImpl::executeDLOAD1()
{
    loadOnTOS(VT_DOUBLE, 1);
    shiftBytecodeIndex(+1);
}

void InterpreterCodeImpl::executeILOAD1()
{
    loadOnTOS(VT_INT, 1);
    shiftBytecodeIndex(+1);
}

void InterpreterCodeImpl::executeDLOADM1()
{
    loadOnTOS(VT_DOUBLE, -1.0);
    shiftBytecodeIndex(+1);
}

void InterpreterCodeImpl::executeILOADM1()
{
    loadOnTOS(VT_INT, -1);
}

void InterpreterCodeImpl::executeDADD()
{
    double d1 = popDoubleFromTOS();
    double d2 = popDoubleFromTOS();
    double dadd = d1 + d2;
    pushDoubleOnTOS(dadd);
    shiftBytecodeIndex(+1);
}

void InterpreterCodeImpl::executeIADD()
{
    int32_t i1 = popInt32FromTOS();
    int32_t i2 = popInt32FromTOS();
    int32_t iadd = i1 + i2;
    pushInt32OnTOS(iadd);
    shiftBytecodeIndex(+1);
}

void InterpreterCodeImpl::executeDSUB()
{
    double d1 = popDoubleFromTOS();
    double d2 = popDoubleFromTOS();
    double dsub = d1 - d2;
    pushDoubleOnTOS(dsub);
    shiftBytecodeIndex(+1);
}

void InterpreterCodeImpl::executeISUB()
{
    int32_t i1 = popInt32FromTOS();
    int32_t i2 = popInt32FromTOS();
    int32_t isub = i1 - i2;
    pushInt32OnTOS(isub);
    shiftBytecodeIndex(+1);
}

void InterpreterCodeImpl::executeDMUL()
{
    double d1 = popDoubleFromTOS();
    double d2 = popDoubleFromTOS();
    double dmul = d1 * d2;
    pushDoubleOnTOS(dmul);
    shiftBytecodeIndex(1);
}

void InterpreterCodeImpl::executeIMUL()
{
    int32_t i1 = popInt32FromTOS();
    int32_t i2 = popInt32FromTOS();
    int32_t imul= i1 * i2;
    pushInt32OnTOS(imul);
    shiftBytecodeIndex(1);
}

void InterpreterCodeImpl::executeDDIV()
{
    double d1 = popDoubleFromTOS();
    double d2 = popDoubleFromTOS();
    double ddiv = d1 / d2;
    pushDoubleOnTOS(ddiv);
    shiftBytecodeIndex(1);
}

void InterpreterCodeImpl::executeIDIV()
{
    int32_t i1 = popInt32FromTOS();
    int32_t i2 = popInt32FromTOS();
    int32_t idiv = i1 / i2;
    pushInt32OnTOS(idiv);
    shiftBytecodeIndex(1);
}

void InterpreterCodeImpl::executeIMOD()
{
    int32_t i1 = popInt32FromTOS();
    int32_t i2 = popInt32FromTOS();
    int32_t imod = i1 % i2;
    pushInt32OnTOS(imod);
    shiftBytecodeIndex(1);
}

void InterpreterCodeImpl::executeDNEG()
{
    double d = popInt32FromTOS();
    double dneg = -d;
    pushDoubleOnTOS(dneg);
    shiftBytecodeIndex(1);
}

void InterpreterCodeImpl::executeINEG()
{
    int32_t i = popInt32FromTOS();
    int32_t ineg = -i;
    pushInt32OnTOS(ineg);
    shiftBytecodeIndex(1);
}

void InterpreterCodeImpl::executeIAOR()
{
    int32_t i1 = popInt32FromTOS();
    int32_t i2 = popInt32FromTOS();
    int32_t iaor = i1 | i2;
    pushInt32OnTOS(iaor);
    shiftBytecodeIndex(1);
}

void InterpreterCodeImpl::executeIAAND()
{
    int32_t i1 = popInt32FromTOS();
    int32_t i2 = popInt32FromTOS();
    int32_t iaand = i1 & i2;
    pushInt32OnTOS(iaand);
    shiftBytecodeIndex(1);
}

void InterpreterCodeImpl::executeIAXOR()
{
    int32_t i1 = popInt32FromTOS();
    int32_t i2 = popInt32FromTOS();
    int32_t iaxor = i1 ^ i2;
    pushInt32OnTOS(iaxor);
    shiftBytecodeIndex(1);
}

void InterpreterCodeImpl::executeIPRINT()
{
    int32_t i = popInt32FromTOS();
    printf("%d\n", i);
    shiftBytecodeIndex(1);
}

void InterpreterCodeImpl::executeDPRINT()
{
    double d = popDoubleFromTOS();
    printf("%.3f\n", d);
    shiftBytecodeIndex(1);
}

void InterpreterCodeImpl::executeSPRINT()
{
    int32_t id = popInt32FromTOS();
    string& constant = constantById((uint16_t)id);
    printf("%s\n", constant);
    shiftBytecodeIndex(1);
}

void InterpreterCodeImpl::executeI2D()
{
    int32_t i = popInt32FromTOS();
    double d = i;
    pushDoubleOnTOS(d);
    shiftBytecodeIndex(1);
}

void InterpreterCodeImpl::executeD2I()
{
    double d = popDoubleFromTOS();
    int32_t i = d;
    pushInt32OnTOS(i);
    shiftBytecodeIndex(1);
}

void InterpreterCodeImpl::executeS2I()
{
    shiftBytecodeIndex(1);
    //    throw InterpretationException("Couldn't cast string to int");
}

void InterpreterCodeImpl::executeSWAP()
{
    //    _stack.swapTwoTopmostElements();
    swapTwoTopmostElements();
    shiftBytecodeIndex(1);
}

void InterpreterCodeImpl::executePOP()
{
    popElementFromTOS();
    shiftBytecodeIndex(1);
}

void InterpreterCodeImpl::executeLOADDVAR0()
{
    double d = loadDoubleFromCurrentScope(0);
    pushDoubleOnTOS(d);
    shiftBytecodeIndex(1);
}

void InterpreterCodeImpl::executeLOADDVAR1()
{
    double d = loadDoubleFromCurrentScope(1);
    pushDoubleOnTOS(d);
    shiftBytecodeIndex(1);
}

void InterpreterCodeImpl::executeLOADDVAR2()
{
    double d = loadDoubleFromCurrentScope(2);
    pushDoubleOnTOS(d);
    shiftBytecodeIndex(1);
}

void InterpreterCodeImpl::executeLOADDVAR3()
{
    double d = loadDoubleFromCurrentScope(3);
    pushDoubleOnTOS(d);
    shiftBytecodeIndex(1);
}

void InterpreterCodeImpl::executeLOADIVAR0()
{
    int32_t i = loadInt32FromCurrentScope(0);
    pushInt32OnTOS(i);
    shiftBytecodeIndex(1);
}

void InterpreterCodeImpl::executeLOADIVAR1()
{
    int32_t i = loadInt32FromCurrentScope(1);
    pushInt32OnTOS(i);
    shiftBytecodeIndex(1);
}

void InterpreterCodeImpl::executeLOADIVAR2()
{
    int32_t i = loadInt32FromCurrentScope(2);
    pushInt32OnTOS(i);
    shiftBytecodeIndex(1);
}

void InterpreterCodeImpl::executeLOADIVAR3()
{
    int32_t i = loadInt32FromCurrentScope(3);
    pushInt32OnTOS(i);
    shiftBytecodeIndex(1);
}

void InterpreterCodeImpl::executeLOADSVAR0()
{
    executeLOADIVAR0();
}

void InterpreterCodeImpl::executeLOADSVAR1()
{
    executeLOADIVAR1();
}

void InterpreterCodeImpl::executeLOADSVAR2()
{
    executeLOADIVAR2();
}

void InterpreterCodeImpl::executeLOADSVAR3()
{
    executeLOADIVAR3();
}

void InterpreterCodeImpl::executeSTOREDVAR0()
{
    double d = popDoubleFromTOS();
    storeDoubleInCurrentScope(0, d);
    shiftBytecodeIndex(1);
}

void InterpreterCodeImpl::executeSTOREDVAR1()
{
    double d = popDoubleFromTOS();
    storeDoubleInCurrentScope(1, d);
    shiftBytecodeIndex(1);
}

void InterpreterCodeImpl::executeSTOREDVAR2()
{
    double d = popDoubleFromTOS();
    storeDoubleInCurrentScope(2, d);
    shiftBytecodeIndex(1);
}

void InterpreterCodeImpl::executeSTOREDVAR3()
{
    double d = popDoubleFromTOS();
    storeDoubleInCurrentScope(3, d);
    shiftBytecodeIndex(1);
}

void InterpreterCodeImpl::executeSTOREIVAR0()
{
    int32_t i = popInt32FromTOS();
    storeInt32InCurrentScope(0, i);
    shiftBytecodeIndex(1);
}

void InterpreterCodeImpl::executeSTOREIVAR1()
{
    int32_t i = popInt32FromTOS();
    storeInt32InCurrentScope(1, i);
    shiftBytecodeIndex(1);
}

void InterpreterCodeImpl::executeSTOREIVAR2()
{
    int32_t i = popInt32FromTOS();
    storeInt32InCurrentScope(2, i);
    shiftBytecodeIndex(1);
}

void InterpreterCodeImpl::executeSTOREIVAR3()
{
    int32_t i = popInt32FromTOS();
    storeInt32InCurrentScope(3, i);
    shiftBytecodeIndex(1);
}

void InterpreterCodeImpl::executeSTORESVAR0()
{
    executeSTOREIVAR0();
}

void InterpreterCodeImpl::executeSTORESVAR1()
{
    executeSTOREIVAR1();
}

void InterpreterCodeImpl::executeSTORESVAR2()
{
    executeSTOREIVAR2();
}

void InterpreterCodeImpl::executeSTORESVAR3()
{
    executeSTOREIVAR3();
}

void InterpreterCodeImpl::executeLOADDVAR()
{
    shiftBytecodeIndex(1);
    uint16_t varId = executedBytecode()->get<uint16_t>(executedBytecodeIndex());
    double d = loadDoubleFromCurrentScope(varId);
    pushDoubleOnTOS(d);
    shiftBytecodeIndex(2);
}

void InterpreterCodeImpl::executeLOADIVAR()
{
    shiftBytecodeIndex(1);
    uint16_t varId = executedBytecode()->get<uint16_t>(executedBytecodeIndex());
    int32_t i = loadInt32FromCurrentScope(varId);
    pushInt32OnTOS(i);
    shiftBytecodeIndex(2);
}

void InterpreterCodeImpl::executeLOADSVAR()
{
    shiftBytecodeIndex(1);
    uint16_t varId = executedBytecode()->get<uint16_t>(executedBytecodeIndex());
    uint16_t constantId = static_cast<uint16_t>(loadInt32FromCurrentScope(varId));
    pushStringOnTOS(constantId);
    shiftBytecodeIndex(2);
}

void InterpreterCodeImpl::executeSTOREDVAR()
{
    shiftBytecodeIndex(1);
    uint16_t varId = executedBytecode()->getUInt16(executedBytecodeIndex());
    shiftBytecodeIndex(2);
    double d = popDoubleFromTOS();
    storeDoubleInCurrentContext(varId, d);
}

void InterpreterCodeImpl::executeSTOREIVAR()
{
    shiftBytecodeIndex(1);
    uint16_t varId = executedBytecode()->getUInt16(executedBytecodeIndex());
    shiftBytecodeIndex(2);
    int32_t i = popInt32FromTOS();
    storeInt32InCurrentContext(varId, i);
}

void InterpreterCodeImpl::executeSTORESVAR()
{
    shiftBytecodeIndex(1);
    uint16_t varId = executedBytecode()->getUInt16(executedBytecodeIndex());
    shiftBytecodeIndex(2);
    uint16_t constantId = popStringFromTOS();
    storeStringInCurrentContext(varId, constantId);
}

void InterpreterCodeImpl::executeLOADCTXDVAR()
{
    shiftBytecodeIndex(1);
    uint16_t scopeId = executedBytecode()->getUInt16(executedBytecodeIndex());
    shiftBytecodeIndex(2);
    uint16_t varId = executedBytecode()->getUInt16(executedBytecodeIndex());
    shiftBytecodeIndex(2);
    double d = loadDoubleFromContext(scopeId, varId);
    pushDoubleOnTOS(d);
}

void InterpreterCodeImpl::executeLOADCTXIVAR()
{
    shiftBytecodeIndex(1);
    uint16_t scopeId = executedBytecode()->getUInt16(executedBytecodeIndex());
    shiftBytecodeIndex(2);
    uint16_t varId = executedBytecode()->getUInt16(executedBytecodeIndex());
    shiftBytecodeIndex(2);
    int32_t i = loadInt32FromContext(scopeId, varId);
    pushInt32OnTOS(i);
}

void InterpreterCodeImpl::executeLOADCTXSVAR()
{
    shiftBytecodeIndex(1);
    uint16_t scopeId = executedBytecode()->getUInt16(executedBytecodeIndex());
    shiftBytecodeIndex(2);
    uint16_t varId = executedBytecode()->getUInt16(executedBytecodeIndex());
    shiftBytecodeIndex(2);
    uint16_t constantId = loadStringFromContext(scopeId, varId);
    pushStringOnTOS(constantId);
}

void InterpreterCodeImpl::executeSTORECTXDVAR()
{}

void InterpreterCodeImpl::executeSTORECTXIVAR()
{}

void InterpreterCodeImpl::executeSTORECTXSVAR()
{}

void InterpreterCodeImpl::executeDCMP()
{
    shiftBytecodeIndex(1);
    double d1 = _stack.popDouble();
    double d2 = _stack.popDouble();
    int32_t cmp = InterpreterCodeImpl::compare(d1, d2);
    _stack.pushInt(cmp);
}

void InterpreterCodeImpl::executeICMP()
{
    shiftBytecodeIndex(1);
    int32_t i1 = _stack.getInt();
    int32_t i2 = _stack.getInt();
    int32_t cmp = InterpreterCodeImpl::compare(i1, i2);
    _stack.pushInt(cmp);
}

void InterpreterCodeImpl::executeJA()
{
    shiftBytecodeIndex(1);
    int16_t offset = bytecode()->getInt16(bytecodeIndex());
    shiftBytecodeIndex(offset);
}

void InterpreterCodeImpl::executeIFICMPNE()
{}

void InterpreterCodeImpl::executeIFICMPE()
{}

void InterpreterCodeImpl::executeIFICMPG()
{}

void InterpreterCodeImpl::executeIFICMPGE()
{}

void InterpreterCodeImpl::executeIFICMPL()
{}

void InterpreterCodeImpl::executeIFICMPLE()
{

}

void InterpreterCodeImpl::executeDUMP()
{
    shiftBytecodeIndex(1);
    VarValue topElement = _stack.getElement();
    switch(topElement.type()) {
    case VT_DOUBLE:
        printf("%.3f\n", topElement.doubleValue());
        break;
    case VT_INT:
        printf("%d\n", topElement.intValue());
        break;
    case VT_STRING:
        printf("%s\n", constantById(topElement.stringIdValue()).c_str());
        break;
    default:
        throw InterpretationException("from DUMP");
        break;
    }
}

void InterpreterCodeImpl::executeSTOP()
{
    shiftBytecodeIndex(1);
    throw InterpretationException("Stopped");
}

void InterpreterCodeImpl::executeCALL()
{
    shiftBytecodeIndex(1);
    uint16_t funcId = bytecode()->getUInt16(bytecodeIndex());
    shiftBytecodeIndex(2);
    BytecodeFunction* bcFunction = dynamic_cast<BytecodeFunction*>(functionById(funcId));
    executeBytecodeFunction(bcFunction);
}

void InterpreterCodeImpl::executeBytecodeFunction(BytecodeFunction* bcFunction) {
    Bytecode* bytecode = bcFunction->bytecode();
    addNewBytecode(bytecode);
    executeBytecode();
    removeLastBytecode();
}

void InterpreterCodeImpl::executeCALLNATIVE()
{
    shiftBytecodeIndex(1);
    uint16_t nativeId = bytecode()->getUInt16(bytecodeIndex());
//    executeNativeFunction(_natives[nativeId]);
    shiftBytecodeIndex(2);
}

void InterpreterCodeImpl::executeNativeFunction(NativeFunctionDescriptor& ) {

}

void InterpreterCodeImpl::executeRETURN()
{
    shiftBytecodeIndex(1);
    setBytecodeIndex(bytecode()->length());
}

void InterpreterCodeImpl::executeBREAK()
{
    //make breakpoint for debugger, may be wait for user's input
}



}
