#include "bytecodegenerator.h"


namespace mathvm {

void BytecodeGenerator::checkNumber(VarType type) {
    if (type != VT_DOUBLE && type != VT_INT) {
        throw TranslationException();
    }
}

BytecodeGenerator::BytecodeGenerator() {
}

BytecodeGenerator::~BytecodeGenerator() {
}

Bytecode* BytecodeGenerator::bytecode() {
    return _bytecodeStack.back();
}

inline Scope* BytecodeGenerator::currentScope() {
    return _currentScope;
}

uint16_t BytecodeGenerator::currentScopeId() {
    return _currentScopeId;
}

void BytecodeGenerator::setCurrentScope(Scope *scope) {
    _currentScope = scope;
}

void BytecodeGenerator::setCurrentScopeId(uint16_t scopeId) {
    _currentScopeId = scopeId;
}

VarType BytecodeGenerator::resolveType(AstNode *node) {
    return _typeInferencer.resolveType(node);
}

VarType BytecodeGenerator::getCommonType(VarType type1, VarType type2) {
    return _typeInferencer.commonType(type1, type2);
}

void BytecodeGenerator::addCast(VarType type, VarType targetType) {
    if (type == targetType) {
        return;
    }

    switch(targetType) {
    case VT_INT:
        if (type == VT_STRING) {
            bytecode()->add(BC_S2I);
            return;
        }
        else if (type == VT_DOUBLE) {
            bytecode()->add(BC_D2I);
            return;
        }
        break;
    case VT_DOUBLE:
        if (type == VT_INT) {
            bytecode()->add(BC_I2D);
            return;
        }
        break;
    default:
        throw TranslationException("from BytecodeGenerator::addCast()");
        break;
    }
}

void BytecodeGenerator::addIntDoubleInsn(VarType type, Instruction intInsn, Instruction doubleInsn) {
    switch(type) {
    case VT_INT:
        bytecode()->add(intInsn);
        break;
    case VT_DOUBLE:
        bytecode()->add(doubleInsn);
        break;
    default:
        throw TranslationException("from BytecodeGenerator::addIntDoubleInsn");
        break;
    }
}

void BytecodeGenerator::addStringIntDoubleInsn(VarType type, Instruction stringInsn, Instruction intInsn, Instruction doubleInsn) {
    switch(type) {
    case VT_STRING:
        bytecode()->add(stringInsn);
        break;
    case VT_INT:
        bytecode()->add(intInsn);
        break;
    case VT_DOUBLE:
        bytecode()->add(doubleInsn);
        break;
    default:
        throw TranslationException("from BytecodeGenerator::addStringIntDoubleInsn");
        break;
    }
}

void BytecodeGenerator::addAdd(VarType type) {
    addIntDoubleInsn(type, BC_IADD, BC_DADD);
}

void BytecodeGenerator::addSub(VarType type) {
    addIntDoubleInsn(type, BC_ISUB, BC_DSUB);
}

void BytecodeGenerator::addMul(VarType type) {
    addIntDoubleInsn(type, BC_IMUL, BC_DMUL);
}

void BytecodeGenerator::addDiv(VarType type) {
    addIntDoubleInsn(type, BC_IDIV, BC_DDIV);
}

void BytecodeGenerator::addMod(VarType type) {
    if (type == VT_INT) {
        bytecode()->add(BC_IMOD);
        return;
    }

    throw TranslationException("from BytecodeGenerator::addMod()");
}

void BytecodeGenerator::addNeg(VarType type) {
    addIntDoubleInsn(type, BC_INEG, BC_DNEG);
}

/*
 * == 0 -> false
 * == 1 -> true
*/

void BytecodeGenerator::addCastIntToBool() {
    Label lJump(bytecode());
    Label lEnd(bytecode());

    bytecode()->add(BC_ILOAD0);
    bytecode()->addBranch(BC_IFICMPE, lJump);
    bytecode()->add(BC_POP);
    bytecode()->add(BC_POP);
    bytecode()->add(BC_ILOAD1);
    bytecode()->addBranch(BC_JA, lEnd);
    bytecode()->bind(lJump);
    bytecode()->add(BC_POP);
    bytecode()->bind(lEnd);
}

void BytecodeGenerator::addCastToBool(VarType type) {
    switch(type) {
    case VT_INT:
        addCastIntToBool();
        break;
    case VT_DOUBLE:
        bytecode()->add(BC_DLOAD0);
        bytecode()->add(BC_DCMP);
        addCastIntToBool();
        break;
    case VT_STRING:
        bytecode()->add(BC_S2I);
        addCastIntToBool();
    default:
        throw TranslationException("from BytecodeGenerator::addCastToBool()");
        break;
    }
}

void BytecodeGenerator::addCompareWith0andReplace(Instruction ifInsn,
                                                  Instruction trueInsn,
                                                  Instruction falseInsn) {
    Label lTrue(bytecode());
    Label lEnd(bytecode());

    bytecode()->add(BC_ILOAD0);
    bytecode()->addBranch(ifInsn, lTrue);
    bytecode()->add(BC_POP);
    bytecode()->add(BC_POP);
    bytecode()->add(falseInsn);
    bytecode()->addBranch(BC_JA, lEnd);
    bytecode()->bind(lTrue);
    bytecode()->add(BC_POP);
    bytecode()->add(BC_POP);
    bytecode()->add(trueInsn);
    bytecode()->bind(lEnd);
}

void BytecodeGenerator::addNot(VarType type) {
    addCastToBool(type);
    addCompareWith0andReplace(BC_IFICMPE, BC_ILOAD1, BC_ILOAD0);
}

void BytecodeGenerator::addCompInsn(VarType type, Instruction insn) {
    switch(type) {
    case VT_INT:
        bytecode()->add(BC_ICMP);
        break;
    case VT_DOUBLE:
        bytecode()->add(BC_DCMP);
        break;
    default:
        throw TranslationException("from BytecodeGenerator::addCompInsn");
        break;
    }

    addCompareWith0andReplace(insn, BC_ILOAD1, BC_ILOAD0);
}

//  +  -  !
void BytecodeGenerator::visitUnaryOpNode(UnaryOpNode *node) {
    AstNode* operand = node->operand();
    operand->visit(this);
    VarType operandType = resolveType(operand);

    TokenKind unOp = node->kind();
    switch(unOp) {
    case tADD:
        checkNumber(operandType);
        break;
    case tSUB:
        addNeg(operandType);
        break;
    case tNOT:
        addNot(operandType);
        break;
    default:
        throw TranslationException("from BytecodeGenerator::visitUnaryOpNode()");
        break;
    }
}

void BytecodeGenerator::addBitOpInsn(VarType type, Instruction insn) {
    if (type == VT_INT) {
        bytecode()->add(insn);
        return;
    }
    throw TranslationException();
}

void BytecodeGenerator::addAAND(VarType type) {
    addBitOpInsn(type, BC_IAAND);
}

void BytecodeGenerator::addAOR(VarType type) {
    addBitOpInsn(type, BC_IAOR);
}

void BytecodeGenerator::addAXOR(VarType type) {
    addBitOpInsn(type, BC_IAXOR);
}

void BytecodeGenerator::addCastTwoLastToBool(VarType type) {
    addCastToBool(type);
    bytecode()->add(BC_SWAP);
    addCastToBool(type);
    bytecode()->add(BC_SWAP);
}

void BytecodeGenerator::visitBinaryOpNode(BinaryOpNode *node)
{
    AstNode* leftOperand = node->left();
    AstNode* rightOperand = node->right();
    TokenKind binOp = node->kind();

    VarType leftType = resolveType(leftOperand);
    checkNumber(leftType);
    VarType rightType = resolveType(rightOperand);
    checkNumber(rightType);
    VarType commonType = getCommonType(leftType, rightType);

    leftOperand->visit(this);
    addCast(leftType, commonType);
    rightOperand->visit(this);
    addCast(rightType, commonType);
    
    switch (binOp) {
    //compare
    case tEQ:
        addCompInsn(commonType, BC_IFICMPE);
        break;
    case tNEQ:
        addCompInsn(commonType, BC_IFICMPNE);
        break;
    case tGE:
        addCompInsn(commonType, BC_IFICMPGE);
        break;
    case tLE:
        addCompInsn(commonType, BC_IFICMPLE);
        break;
    case tGT:
        addCompInsn(commonType, BC_IFICMPG);
        break;
    case tLT:
        addCompInsn(commonType, BC_IFICMPL);
        break;
        //logic
    case tOR:
        addCastTwoLastToBool(commonType);
        addAdd(commonType);
        break;
    case tAND:
        addCastTwoLastToBool(commonType);
        addMul(commonType);
        break;
        //bit
    case tAOR:
        addAOR(commonType);
        break;
    case tAAND:
        addAAND(commonType);
        break;
    case tAXOR:
        addAXOR(commonType);
        break;
        //ariphm
    case tADD:
        addAdd(commonType);
        break;
    case tSUB:
        addSub(commonType);
        break;
    case tMUL:
        addMul(commonType);
        break;
    case tDIV:
        addDiv(commonType);
        break;
    case tMOD:
        addMod(commonType);
        break;
    case tRANGE:
        break;
    default:
        throw TranslationException("from BytecodeGenerator::visitBinaryOpNode()");
        break;
    }
}

void BytecodeGenerator::visitIntLiteralNode(IntLiteralNode *node)
{
    bytecode()->add(BC_ILOAD);
    bytecode()->addInt64(node->literal());
}

void BytecodeGenerator::visitDoubleLiteralNode(DoubleLiteralNode *node)
{
    bytecode()->add(BC_DLOAD);
    bytecode()->addDouble(node->literal());
}

uint16_t BytecodeGenerator::registerConstant(string const& constant) {
    return _code->makeStringConstant(constant);
}

void BytecodeGenerator::visitStringLiteralNode(StringLiteralNode *node) {
    uint16_t id = registerConstant(node->literal());
    bytecode()->add(BC_SLOAD);
    bytecode()->addUInt16(id);
}

void BytecodeGenerator::loadValueFromVar(uint16_t scopeId,
                                         uint16_t varId,
                                         VarType varType) {
    switch(varType) {
    case VT_INT:
        bytecode()->add(BC_LOADCTXIVAR);
        break;
    case VT_DOUBLE:
        bytecode()->add(BC_LOADCTXDVAR);
        break;
    case VT_STRING:
        bytecode()->add(BC_LOADCTXSVAR);
        break;
    default:
        throw TranslationException();
        break;
    }

    bytecode()->addUInt16(scopeId);
    bytecode()->addUInt16(varId);
}

void BytecodeGenerator::storeValueToVar(uint16_t scopeId,
                                        uint16_t varId,
                                        VarType varType) {
    switch(varType) {
    case VT_INT:
        bytecode()->add(BC_STORECTXIVAR);
        break;
    case VT_DOUBLE:
        bytecode()->add(BC_STORECTXDVAR);
        break;
    case VT_STRING:
        bytecode()->add(BC_STORECTXSVAR);
        break;
    default:
        throw TranslationException();
        break;
    }

    bytecode()->addUInt16(scopeId);
    bytecode()->addUInt16(varId);
}

//  =  +=  -=
void BytecodeGenerator::visitStoreNode(StoreNode *node) {
    TokenKind op = node->op();
    const AstVar* var = node->var();
    VarType varType = var->type();

    uint16_t scopeId = currentScopeId();
    uint16_t varId = getVarId(scopeId, var->name());

    AstNode* value = node->value();
    value->visit(this); // after this operation on TOS lies value which i must store
    VarType valueType = resolveType(value);
    addCast(valueType, varType);

    if (op == tINCRSET) {
        loadValueFromVar(scopeId, varId, varType);
        addAdd(varType);
    }
    else if (op == tDECRSET) {
        loadValueFromVar(scopeId, varId, varType);
        addSub(varType);
    }

    storeValueToVar(scopeId, varId, varType);
}

void BytecodeGenerator::visitLoadNode(LoadNode *node)
{
    const AstVar* var = node->var();
    pair<uint16_t, uint16_t> scopeVarId = findScopeVarId(currentScope(), var->name());
    uint16_t scopeId = scopeVarId.first;
    uint16_t varId = scopeVarId.second;
    loadValueFromVar(scopeId, varId, var->type());
}

void BytecodeGenerator::visitBlockNode(BlockNode *node) {

    Scope* prevScope = currentScope();
    uint16_t prevScopeId = currentScopeId();

    Scope* blockScope = node->scope();
    uint16_t blockScopeId = registerScope(blockScope);
    setCurrentScope(blockScope);
    setCurrentScopeId(blockScopeId);

    for (size_t i = 0; i < node->nodes(); ++i) {
        node->nodeAt(i)->visit(this);
    }

    setCurrentScope(prevScope);
    setCurrentScopeId(prevScopeId);
}

void BytecodeGenerator::visitIfNode(IfNode *node) {

    AstNode* ifExpr = node->ifExpr();
    ifExpr->visit(this);
    VarType ifExprType = resolveType(ifExpr);
    addCastToBool(ifExprType);

    Label lElse(bytecode());
    Label lEndIf(bytecode());

    bytecode()->add(BC_ILOAD0);
    bytecode()->addBranch(BC_IFICMPE, lElse);
    bytecode()->add(BC_POP);
    //maybe add pop value of if expr
    BlockNode* thenBlock = node->thenBlock();
    thenBlock->visit(this);
    bytecode()->addBranch(BC_JA, lEndIf);

    bytecode()->bind(lElse);
    bytecode()->add(BC_POP);
    //maybe add pop value of if expr
    BlockNode* elseBlock = node->elseBlock();
    if (elseBlock) {
        thenBlock->visit(this);
    }
    bytecode()->bind(lEndIf);
}

void BytecodeGenerator::visitWhileNode(WhileNode *node) {
    AstNode* whileExpr = node->whileExpr();
    BlockNode* whileBlock = node->loopBlock();

    Label lBegin(bytecode());
    Label lEnd(bytecode());

    bytecode()->bind(lBegin);
    whileExpr->visit(this);
    bytecode()->add(BC_ILOAD0);
    bytecode()->addBranch(BC_IFICMPE, lEnd);

    bytecode()->add(BC_POP);
    whileBlock->visit(this);

    bytecode()->addBranch(BC_JA, lBegin);
    bytecode()->bind(lEnd);
    bytecode()->add(BC_POP);
}

uint16_t BytecodeGenerator::getVarId(uint16_t scopeId, string const& name) {
    VarMap& vars = _vars[scopeId];
    for (VarMap::iterator varIt = vars.begin(); varIt != vars.end(); ++varIt) {
        const string& varName = varIt->first->name();
        if (varName == name) {
            return varIt->second;
        }
    }

    throw TranslationException();
}

std::pair<uint16_t, uint16_t> BytecodeGenerator::findScopeVarId(Scope* scope, const string& varName) {
    while (scope != 0) {
        uint16_t scopeId = _scopes[scope];
        Scope::VarIterator varIt(scope);
        while(varIt.hasNext()) {
            AstVar* var = varIt.next();
            if (var->name() == varName) {
                uint16_t varId = getVarId(scopeId, varName);
                return std::pair<uint16_t, uint16_t>(scopeId, varId);
            }
        }
        scope = scope->parent();
    }

    throw TranslationException();
}

std::pair<uint16_t, uint16_t> BytecodeGenerator::findScopeVarId(const string &name) {
    return findScopeVarId(currentScope(), name);
}

void BytecodeGenerator::visitForNode(ForNode *node) {
    const AstVar* inVar = node->var();
    VarType inVarType = inVar->type();
    string inVarName = inVar->name();

    AstNode* inExpr = node->inExpr();
    inExpr->visit(this); // left on preTOS, right on TOS,
    VarType rangeType = resolveType(inExpr);
    addCast(rangeType, inVarType);
    bytecode()->add(BC_SWAP);
    addCast(rangeType, inVarType); // left on TOS, right below

    BlockNode* forBlock = node->body();
    Scope* forScope = forBlock->scope();
    uint16_t blockScopeId = registerScope(forScope);

    std::pair<uint16_t, uint16_t> inScopeVarId = findScopeVarId(forScope, inVarName);
    uint16_t scopeId = inScopeVarId.first;
    uint16_t inVarId = inScopeVarId.second;

    uint16_t leftRangeId = registerVar(blockScopeId, new AstVar("<left>", VT_INT, currentScope()));
    uint16_t rightRangeId = registerVar(blockScopeId, new AstVar("<right>", VT_INT, currentScope()));

    storeValueToVar(blockScopeId, leftRangeId, inVarType);
    storeValueToVar(blockScopeId, rightRangeId, inVarType);

    Label forBegin(bytecode());
    Label forEnd(bytecode());

    forBegin.bind(bytecode()->length());

    loadValueFromVar(blockScopeId, leftRangeId, inVarType);
    storeValueToVar(scopeId, inVarId, inVarType);

    loadValueFromVar(blockScopeId, rightRangeId, inVarType);
    loadValueFromVar(scopeId, inVarId, inVarType);

    bytecode()->addBranch(BC_IFICMPG, forEnd);

    forBlock->visit(this);
    loadValueFromVar(blockScopeId, leftRangeId, inVarType);
    bytecode()->add(BC_ILOAD1); // only increase range
    bytecode()->add(BC_IADD);
    storeValueToVar(blockScopeId, leftRangeId, inVarType);

    bytecode()->addBranch(BC_JA, forBegin);

    forEnd.bind(bytecode()->length());
}

uint16_t BytecodeGenerator::translatedFunctionId() {
    return _bcFunctionStack.back();
}

void BytecodeGenerator::addReturn()
{
    bytecode()->add(BC_RETURN);
}

void BytecodeGenerator::visitReturnNode(ReturnNode *node) {
    uint16_t id = translatedFunctionId();
    BytecodeFunction* bcFunction = _bcFunctions[id];
    VarType targetReturnType = bcFunction->returnType();

    AstNode* returnExpr = node->returnExpr();
    if (returnExpr != NULL) {
        returnExpr->visit(this);
        VarType returnExprType = resolveType(returnExpr);
        addCast(returnExprType, targetReturnType);
    }
    addReturn();
}

void BytecodeGenerator::addPrint(VarType type) {
    switch(type) {
    case VT_INT:
        bytecode()->add(BC_IPRINT);
        break;
    case VT_DOUBLE:
        bytecode()->add(BC_DPRINT);
        break;
    case VT_STRING:
        bytecode()->add(BC_SPRINT);
        break;
    default:
        throw TranslationException("from BytecodeGenerator::addPrint()");
        break;
    }
}

void BytecodeGenerator::visitPrintNode(PrintNode *node) {
    for (uint32_t i = 0; i < node->operands(); ++i) {
        AstNode* operand = node->operandAt(i);
        operand->visit(this);
        VarType operandType = resolveType(operand);
        addPrint(operandType);
    }
}

void BytecodeGenerator::visitNativeCallNode(NativeCallNode *node) {
//    uint16_t id = _nativeById.size();
//    _nativeById[node->nativeName()] = id;

//    NativeFunctionDescriptor nativeDesc(node->nativeName(), node->nativeSignature(), 0);
//    _natives.push_back(nativeDesc);

    _code->makeNativeFunction(node->nativeName(), node->nativeSignature(), NULL);
}

AstFunction* BytecodeGenerator::getFunction(Scope* scope, const string& name) {
    while(scope != 0) {
        Scope::FunctionIterator functionIt(scope);
        while(functionIt.hasNext()) {
            AstFunction* astFunction = functionIt.next();
            if (astFunction->name() == name) {
                return astFunction;
            }
        }
        scope = scope->parent();
    }

    throw TranslationException();
}

uint16_t BytecodeGenerator::getFunctionId(Scope* scope, const string& name) {
    AstFunction* astFunction = getFunction(scope, name);
    return _astFunctions[astFunction];
}

void BytecodeGenerator::visitCallNode(CallNode *node) {
    string callName = node->name();
    AstFunction* function = getFunction(currentScope(), callName);
    uint16_t id = _astFunctions[function];
    bytecode()->add(BC_CALL);
    bytecode()->addInt16(id);
    if (node->parametersNumber() != function->parametersNumber()) {
        throw TranslationException();
    }

    for (int i = node->parametersNumber() - 1; i > -1; --i) {
        AstNode* arg = node->parameterAt(i);
        arg->visit(this);
        VarType argType = resolveType(arg);
        VarType paramType = function->parameterType(i);
        addCast(argType, paramType);
    }
}


//arguments lies on stack in reverse order: first on TOS, than below second and etc.
//regster function name
void BytecodeGenerator::visitFunctionNode(FunctionNode *node) {
    Scope* signatureScope = node->body()->scope()->parent();
    uint16_t signatureScopeId = registerScope(signatureScope);

    Scope::VarIterator signatureVarIt(signatureScope, false);
    while (signatureVarIt.hasNext()) {
        AstVar* var = signatureVarIt.next();
        uint16_t varId = registerVar(signatureScopeId, var);
        storeValueToVar(signatureScopeId, varId, var->type());
    }

    node->body()->visit(this);
}

void BytecodeGenerator::visitAstFunction(AstFunction* astFunction) {
    uint16_t id = registerFunction(astFunction);
    BytecodeFunction* bcFunction = _bcFunctions[id];

    FunctionNode* function = astFunction->node();
    Scope* signatureScope = function->body()->scope()->parent();
    registerScope(signatureScope);
    Scope* bodyScope = function->body()->scope();
    uint16_t bodyScopeId = registerScope(bodyScope);

    bcFunction->setScopeId(bodyScopeId);

    _bcFunctionStack.push_back(id);
    _bytecodeStack.push_back(bcFunction->bytecode());

    function->visit(this);

    _bytecodeStack.pop_back();
    _bcFunctionStack.pop_back();
}

uint16_t BytecodeGenerator::registerFunction(AstFunction* astFunction) {
    if (_astFunctions.find(astFunction) != _astFunctions.end()) {
        return _astFunctions[astFunction];
    }
    uint16_t id = _bcFunctions.size();
    _astFunctions[astFunction] = id;
    BytecodeFunction* bcFunction = new BytecodeFunction(astFunction);
    //bcFunction->assignId(id);
    _bcFunctions.push_back(bcFunction);

    return id;
}

uint16_t BytecodeGenerator::registerVar(uint16_t scopeId, AstVar* var) {
    VarMap& vars = _vars[scopeId];
    uint16_t id = vars.size();
    vars[var] = id;

    return id;
}

uint16_t BytecodeGenerator::registerScope(Scope * scope) {
    if (_scopes.find(scope) != _scopes.end()) {
        return _scopes[scope];
    }
    uint16_t id = _scopes.size();
    _scopes[scope] = id;

    Scope::FunctionIterator functionIt(scope);
    while(functionIt.hasNext()) {
        AstFunction* astFunction = functionIt.next();
        registerFunction(astFunction);
    }

    Scope::VarIterator varIt(scope);
    while(varIt.hasNext()) {
        AstVar* var = varIt.next();
        registerVar(id, var);
    }

    functionIt = Scope::FunctionIterator(scope);
    while(functionIt.hasNext()) {
        AstFunction* astFunction = functionIt.next();
        visitAstFunction(astFunction);
    }

    return id;
}

InterpreterCodeImpl* BytecodeGenerator::makeBytecode(AstFunction* top) {
    _code = new InterpreterCodeImpl();
    visitAstFunction(top);

    for (BytecodeFunctionVec::const_iterator bcFunctionIt = _bcFunctions.begin(); bcFunctionIt != _bcFunctions.end(); ++bcFunctionIt) {
        _code->addFunction(*bcFunctionIt);
    }

    return _code;
}

}

// void *code = dlsym(RTLD_DEFAULT, node->nativeName().c_str());
