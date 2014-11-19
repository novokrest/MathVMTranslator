#include "BytecodeGenerator.h"

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

BytecodeGenerator::BytecodeVar BytecodeGenerator::findVarId(Scope* scope, const string& name) {
    while (scope != 0) {
        uint16_t scopeId = getScopeId(scope);
        Scope::VarIterator varIt(scope);
        while(varIt.hasNext()) {
            AstVar* var = varIt.next();
            if (var->name() == name) {
                uint16_t varId = getVarId(scopeId, name);
                return std::pair<uint16_t, uint16_t>(scopeId, varId);
            }
        }
        scope = scope->parent();
    }

    throw TranslatorException();
}

BytecodeGenerator::BytecodeVar BytecodeGenerator::findVarId(const string &name) {
    return getVarId(currentScope, name);
}

uint16_t BytecodeGenerator::getVarId(uint16_t scopeId, const string& name) {

}

// string -> int -> double
void BytecodeGenerator::addCast(VarType type, VarType targetType) {
    if (type == targetType) {
        return;
    }
    if (targetType == VT_INT) {
        if (type == VT_STRING) {
            _bytecode.add(BC_S2I);
        }
        else if (type == VT_DOUBLE) {
            _bytecode.add(BC_D2I);
        }
    }
    else if (targetType == VT_DOUBLE) {
        if (type == VT_STRING) {
            _bytecode.add(BC_S2I);
        }
        _bytecode.add(BC_I2D);
    }
}

void BytecodeGenerator::addOp(VarType type, Instruction intInsn, Instruction doubleInsn) {
    switch(type) {
    case VT_INT:
        bytecode()->add(intInsn);
        break;
    case VT_DOUBLE:
        bytecode()->add(doubleInsn);
        break;
    default:
        throw TranslatorException();
        break;
    }
}

void BytecodeGenerator::addAdd(VarType type) {
    addOp(type, BC_IADD, BC_DADD);
}

void BytecodeGenerator::addSub(VarType type) {
    addOp(type, BC_ISUB, BC_DSUB);
}

void BytecodeGenerator::addMul(VarType type) {
    addOp(type, BC_IMUL, BC_DMUL);
}

void BytecodeGenerator::addDiv(VarType type) {
    addOp(type, BC_IDIV, BC_DDIV);
}

void BytecodeGenerator::addMod(VarType type) {
    if (type == VT_INT) {
        bytecode()->add(BC_IMOD);
    }

    throw TranslatorException();
}

void BytecodeGenerator::addNeg(VarType type) {
    addOp(type, BC_INEG, BC_DNEG);
}

void BytecodeGenerator::addIf0(Instruction zeroInsn,
                               Instruction ifInsn,
                               Instruction thenInsn,
                               Instruction elseInsn) {
    Label lElse(bytecode());
    Label lEnd(bytecode());

    bytecode()->add(zeroInsn);
    bytecode()->addBranch(ifInsn, lElse);
    bytecode()->add(thenInsn);
    bytecode()->addBranch(BC_JA, lEnd);
    lElse.bind(bytecode()->length());
    bytecode()->add(elseInsn);
    lEnd.bind(bytecode()->length());
}

void BytecodeGenerator::addNot(VarType type) {
    assertNumber(type);

    if (type == VT_DOUBLE) {
        bytecode()->add(BC_DLOAD0);
        bytecode()->add(BC_DCMP);
    }

    Label lElse(bytecode());
    Label lEnd(bytecode());
    bytecode()->add(BC_ILOAD0);
    //if
    bytecode()->add(BC_IFICMPE);
    lElse.addRelocation(bytecode()->length());
    //then
    bytecode()->add(BC_ILOAD0);
    lEnd.addRelocation(bytecode()->length());
    //else
    lElse.bind(bytecode()->length());
    bytecode()->add(BC_ILOAD1);
    //end if
    lEnd.bind(bytecode()->length());
}

//  +  -  !
void BytecodeGenerator::visitUnaryOpNode(UnaryOpNode *node) {
    AstNode* operand = node->operand();
    operand->visit(this);
    VarType operandType = _typeInferencer.resolveType(operand);

    TokenKind unOp = node->kind();
    switch(unOp) {
    case tADD:
        assertNumber(operandType);
        break;
    case tSUB:
        addNeg(operandType);
        break;
    case tNOT:
        addNot(operandType);
        break;
    }
}

void BytecodeGenerator::addGE(VarType type) {
    assertNumber(type);

    Label lElse(bytecode());
    Label lEndIf(bytecode());
    bytecode()->add(BC_SWAP);
    bytecode()->add(type == VT_DOUBLE ? BC_DCMP ? BC_ICMP);
    bytecode()->add(BC_ILOAD0);
    bytecode()->addBranch(BC_IFICMPG, lElse);
    bytecode()->add(BC_ILOAD1);
    bytecode()->addBranch(BC_JA, lEndIf);
    lElse.bind(bytecode()->length());
    bytecode()->add(BC_ILOAD0);
    lEndIf.bind(bytecode()->length());
}

void BytecodeGenerator::addGT(VarType type) {
    assertNumber(type);

    Label lElse(bytecode());
    Label lEndIf(bytecode());
    bytecode()->add(BC_SWAP);
    bytecode()->add(type == VT_DOUBLE ? BC_DCMP ? BC_ICMP);
    bytecode()->add(BC_ILOAD0);
    bytecode()->addBranch(BC_IFICMPGE, lElse);
    bytecode()->add(BC_ILOAD1);
    bytecode()->addBranch(BC_JA, lEndIf);
    lElse.bind(bytecode()->length());
    bytecode()->add(BC_ILOAD0);
    lEndIf.bind(bytecode()->length());
}

void BytecodeGenerator::addIf0(Instruction zeroInsn,
                               Instruction ifInsn,
                               Instruction thenInsn,
                               Instruction elseInsn) {
    Label lElse(bytecode());
    Label lEnd(bytecode());

    bytecode()->add(zeroInsn);
    bytecode()->addBranch(ifInsn, lElse);
    bytecode()->add(thenInsn);
    bytecode()->addBranch(BC_JA, lEnd);
    lElse.bind(bytecode()->length());
    bytecode()->add(elseInsn);
    lEnd.bind(bytecode()->length());
}

void BytecodeGenerator::addCompInsn(Instruction ifInsn, VarType type) {
    bytecode()->add(BC_SWAP);
    addOp(type, BC_ICMP, BC_DCMP);
    addIf0(ifInsn, BC_ILOAD0, BC_ILOAD0, BC_ILOAD1);
}

void BytecodeGenerator::visitBinaryOpNode(BinaryOpNode *node)
{
    AstNode* leftOperand = node->left();
    AstNode* rightOperand = node->right();
    TokenKind binOp = node->kind();

    VarType leftType = _typeInferencer.resolveType(leftOperand);
    checkNumber(leftType);
    VarType rightType = _typeInferencer.resolveType(rightOperand);
    checkNumber(rightType);
    VarType commonType = _typeInferencer.commonType(leftType, rightType);

    leftOperand->visit(this);
    addCast(leftType, commonType);
    rightOperand->visit(this);
    addCast(rightType, commonType);
    
    switch (binOp) {
        //compare
    case tEQ:
        addCompInsn(BC_IFICMPE, commonType);
        break;
    case tNEQ:
        addCompInsn(BC_IFICMPNE, commonType);
        break;
    case tGE:
        addCompInsn(BC_IFICMPGE, commonType);
        break;
    case tLE:
        addCompInsn(BC_IFICMPLE, commonType);
        break;
    case tGT:
        addCompInsn(BC_IFICMPG, commonType);
        break;
    case tLT:
        addCompInsn(BC_IFICMPL, commonType);
        break;
        //logic
    case tOR:
        addAdd(commonType);
        break;
    case tAND:
        addMul(commonType);
        break;
        //bit
    case tAOR:
        if (commonType != VT_INT) {
            throw TranslationException();
        }
        bytecode()->add(BC_IAOR);
        break;
    case tAAND:
        if (commonType != VT_INT) {
            throw TranslationException();
        }
        bytecode()->add(BC_IAAND);
        break;
    case tAXOR:
        if (commonType != VT_INT) {
            throw TranslationException();
        }
        bytecode()->add(BC_IAXOR);
        break;
        //ariphm
    case tADD:
        addAdd();
        break;
    case tSUB:
        addSub();
        break;
    case tMUL:
        addMul();
        break;
    case tDIV:
        addDiv();
        break;
    case tMOD:
        addMod();
        break;
    default:
        throw TranslationException();
        break;
    }
}

void BytecodeGenerator::visitIntLiteralNode(IntLiteralNode *node)
{
    _bytecode.add(BC_ILOAD);
    _bytecode.addInt64(node->literal());
}

void BytecodeGenerator::visitDoubleLiteralNode(DoubleLiteralNode *node)
{
    _bytecode.add(BC_DLOAD);
    _bytecode.addDouble(node->literal());
}

uint16_t BytecodeGenerator::registerConstant(string const& constant) {
    uint16_t id = _constants.size();
    _constantById[constant] = id;
    _constants.push_back(constant);

    return id;
}

void BytecodeGenerator::visitStringLiteralNode(StringLiteralNode *node) {
    uint16_t id = registerConstant(node->literal());
    bytecode().add(BC_SLOAD);
    bytecode().addInt16(id);
}

void BytecodeGenerator::loadValueFromVar(uint16_t scopeId,
                                         uint16_t varId,
                                         VarType varType) {
    switch(varType) {
    case VT_INT:
        bytecode().add(BC_LOADCTXIVAR);
        break;
    case VT_DOUBLE:
        bytecode().add(BC_LOADCTXDVAR);
        break;
    case VT_STRING:
        bytecode().add(BC_LOADCTXSVAR);
    default:
        throw TranslationException();
        break;
    }

    bytecode().addInt16(scopeId);
    bytecode().addInt16(varId);
}

void BytecodeGenerator::storeValueToVar(uint16_t scopeId,
                                        uint16_t varId,
                                        VarType varType) {
    switch(varType) {
    case VT_INT:
        bytecode().add(BC_STORECTXIVAR);
        break;
    case VT_DOUBLE:
        bytecode().add(BC_STORECTXDVAR);
        break;
    case VT_STRING:
        bytecode().add(BC_STORECTXSVAR);
    default:
        assert(false);
        break;
    }

    bytecode().addInt16(scopeId);
    bytecode().addInt16(varId);
}

//  =  +=  -=
void BytecodeGenerator::visitStoreNode(StoreNode *node) {
    TokenKind op = node->op();
    AstVar* var = node->var();
    VarType varType = var->type();

    uint16_t scopeId = currentScopeId();
    uint16_t varId = varId(scopeId, var->name());

    AstNode* value = node->value();
    value->visit(this); // after this operation on TOS lies value which i must store
    VarType valueType = _typeInferencer.resolveType(value);
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
    AstVar* var = node->var();
    uint16_t scopeId = currentScopeId();
    uint16_t varId = varId(scopeId, var->name());
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

    Label lElse(bytecode());
    Label lEndIf(bytecode());
    bytecode()->add(BC_ILOAD0);

    //jump if double == 0 -> false
    bytecode()->addBranch(BC_IFICMPE, lElse);

    BlockNode* thenBlock = node->thenBlock();
    thenBlock->visit(this);
    bytecode()->addBranch(BC_JA, lEndIf);

    lElse.bind(bytecode()->length());
    BlockNode* elseBlock = node->elseBlock();
    if (elseBlock) {
        thenBlock->visit(this);
    }

    lEndIf.bind(bytecode()->length());
}

void BytecodeGenerator::visitWhileNode(WhileNode *node) {
    AstNode* whileExpr = node->whileExpr();
    BlockNode* whileBlock = node->loopBlock();

    Label lBegin(bytecode());
    Label lEnd(bytecode());

    lBegin.bind(bytecode()->length());
    whileExpr->visit(this);
    bytecode()->add(BC_ILOAD0);
    bytecode()->addBranch(BC_IFICMPE, lEnd);
    whileBlock->visit(this);
    bytecode()->addBranch(BC_JA, lBegin);
    lEnd.bind(bytecode()->length());
}

void BytecodeGenerator::visitForNode(ForNode *node) {
    AstNode* inExpr = node->inExpr();
    inExpr->visit(this); // left on preTOS, right on TOS,
    VarType rangeType = _typeInferencer.resolveType(inExpr);

    AstVar* inVar = node->var();
    VarType inVarType = inVar->type();
    string inVarName = inVar->name();

    //TODO:add casts
    BlockNode* forBlock = node->body();
    uint16_t blockScopeId = registerScope(forBlock->scope());
    uint16_t inVarId = getVarId(blockScopeId, inVarName);
    uint16_t leftRangeId = registerVar(blockScopeId, new AstVar("<left>", VT_INT, currentScope()));
    uint16_t rightRangeId = registerVar(blockScopeId, new AstVar("<right>", VT_INT, currentScope()));

    storeValueToVar(blockScopeId, rightRangeId, inVarType);
    storeValueToVar(blockScopeId, leftRangeId, inVarType);

    Label forBegin(bytecode());
    Label forEnd(bytecode());

    forBegin.bind(bytecode()->length());

    loadValueFromVar(blockScopeId, leftRangeId, inVarType);
    storeValueToVar(blockScopeId, inVarId, inVarType);

    loadValueFromVar(blockScopeId, rightRangeId, inVarType);
    loadValueFromVar(blockScopeId, inVarId, inVarType);

    bytecode()->addBranch(BC_IFICMPG, forEnd);

    forBlock->visit(this);
    loadValueFromVar(blockScopeId, leftRangeId, inVarType);
    bytecode()->add(BC_ILOAD1); // only increase range
    bytecode()->add(BC_IADD);
    storeValueToVar(blockScopeId, leftRangeId, inVarType);

    bytecode()->addBranch(BC_JA, forBegin);

    forEnd.bind(bytecode()->length());
}

void BytecodeGenerator::visitReturnNode(ReturnNode *node) {
    uint16_t tFunctionId = currentTranslatedFunction();
    TranslatedFunction tFunction = getTranslatedFunctionById(tFunctionId);
    VarType targetReturnType = tFunction.returnType();

    AstNode* returnExpr = node->returnExpr();
    returnExpr->visit(this);
    VarType returnExprType = _typeInferencer.resolveType(returnExpr);
    addCast(returnExprType, targetReturnType);
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
        throw TranslationException();
        break;
    }
}

void BytecodeGenerator::visitPrintNode(PrintNode *node) {
    for (uint32_t i = 0; i < node->operands(); ++i) {
        AstNode* operand = node->operandAt(i);
        operand->visit(this);
        VarType operandType = _typeInferencer.resolveType(operand);
        addPrint(operandType);
    }
}

void BytecodeGenerator::visitNativeCallNode(NativeCallNode *node) {
    uint16_t id = _nativeById.size();
    _nativeById[node->nativeName()] = id;

    NativeFunctionDescriptor nativeDesc(node->nativeName(), node->nativeSignature(), 0);
    _natives.push_back(nativeDesc);
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
    if (node->parametersNumber() != function->parametersNumber()) {
        throw TranslationException();
    }

    for (int i = node->parametersNumber() - 1; i > -1; --i) {
        AstNode* arg = node->parameterAt(i);
        arg->visit(this);
        VarType argType = _typeInferencer.resolveType(arg);
        VarType paramType = function->parameterType(i);
        addCast(argType, paramType);
    }
    uint16_t id = _astFunctions[function];
    bytecode()->add(BC_CALL);
    bytecode()->addInt16(id);
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
    bcFunction->assignId(id);
    _bcFunctions.push_back(bcFunction);

    return id;
}

uint16_t BytecodeGenerator::registerVar(uint16_t scopeId, AstVar* var) {
    VarMap& vars = _vars[scopeId];
    uint16_t id = vars.size();
    vars[var->name()] = id;

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

}

// void *code = dlsym(RTLD_DEFAULT, node->nativeName().c_str());
