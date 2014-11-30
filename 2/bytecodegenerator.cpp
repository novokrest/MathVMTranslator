#include "bytecodegenerator.h"


namespace mathvm {

void BytecodeGenerator::checkNumber(VarType type) {
    if (type != VT_DOUBLE && type != VT_INT) {
        throw TranslationException();
    }
}

BytecodeGenerator::BytecodeGenerator()
    : _lastType(VT_INVALID) {
}

BytecodeGenerator::~BytecodeGenerator() {
}

Bytecode* BytecodeGenerator::bytecode() {
    return _bytecodeStack.back();
}

//inline Scope* BytecodeGenerator::currentScope() {
//    return _currentScope;
//}

//uint16_t BytecodeGenerator::currentScopeId() {
//    return _currentScopeId;
//}

//void BytecodeGenerator::setCurrentScope(Scope *scope) {
//    _currentScope = scope;
//}

//void BytecodeGenerator::setCurrentScopeId(uint16_t scopeId) {
//    _currentScopeId = scopeId;
//}

//VarType BytecodeGenerator::resolveType(AstNode *node) {
//    return _typeInferencer.resolveType(node);
//}

VarType BytecodeGenerator::lastInferredType() {
    return _lastType;
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
//    bytecode()->add(BC_POP);
//    bytecode()->add(BC_POP);
    bytecode()->add(BC_ILOAD1);
    bytecode()->addBranch(BC_JA, lEnd);
    bytecode()->bind(lJump);
    bytecode()->add(BC_ILOAD0);
//    bytecode()->add(BC_POP);
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
    addSwap();
    bytecode()->addBranch(ifInsn, lTrue);
//    bytecode()->add(BC_POP);
//    bytecode()->add(BC_POP);
    bytecode()->add(falseInsn);
    bytecode()->addBranch(BC_JA, lEnd);
    bytecode()->bind(lTrue);
//    bytecode()->add(BC_POP);
//    bytecode()->add(BC_POP);
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
    VarType operandType = lastInferredType();// resolveType(operand);

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

    _lastType = operandType;
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
    addSwap();
    addCastToBool(type);
    addSwap();
}

void BytecodeGenerator::visitBinaryOpNode(BinaryOpNode *node)
{
    AstNode* leftOperand = node->left();
    AstNode* rightOperand = node->right();
    TokenKind binOp = node->kind();

    leftOperand->visit(this);
    VarType leftType = lastInferredType(); //resolveType(leftOperand);
    checkNumber(leftType);

    rightOperand->visit(this);
    VarType rightType = lastInferredType();// resolveType(rightOperand);
    checkNumber(rightType);

    VarType commonType = getCommonType(leftType, rightType);
    addSwap();
    addCast(leftType, commonType);
    addSwap();
    addCast(rightType, commonType);
    
    _lastType = commonType;

    switch (binOp) {
    //compare
    case tEQ:
        addSwap();
        addCompInsn(commonType, BC_IFICMPE);
        _lastType = VT_INT;
        break;
    case tNEQ:
        addSwap();
        addCompInsn(commonType, BC_IFICMPNE);
        _lastType = VT_INT;
        break;
    case tGE:
        addSwap();
        addCompInsn(commonType, BC_IFICMPGE);
        _lastType = VT_INT;
        break;
    case tLE:
        addSwap();
        addCompInsn(commonType, BC_IFICMPLE);
        _lastType = VT_INT;
        break;
    case tGT:
        addSwap();
        addCompInsn(commonType, BC_IFICMPG);
        _lastType = VT_INT;
        break;
    case tLT:
        addSwap();
        addCompInsn(commonType, BC_IFICMPL);
        _lastType = VT_INT;
        break;
        //logic
    case tOR:
        addCastTwoLastToBool(commonType);
        addAdd(commonType);
        _lastType = VT_INT;
        break;
    case tAND:
        addCastTwoLastToBool(commonType);
        addMul(commonType);
        _lastType = VT_INT;
        break;
        //bit
    case tAOR:
        addAOR(commonType);
        _lastType = VT_INT;
        break;
    case tAAND:
        addAAND(commonType);
        _lastType = VT_INT;
        break;
    case tAXOR:
        addAXOR(commonType);
        _lastType = VT_INT;
        break;
        //ariphm
    case tADD:
        addAdd(commonType);
        break;
    case tSUB:
        addSwap();
        addSub(commonType);
        break;
    case tMUL:
        addMul(commonType);
        break;
    case tDIV:
        addSwap();
        addDiv(commonType);
        break;
    case tMOD:
        addSwap();
        addMod(commonType);
        _lastType = VT_INT;
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

    _lastType = VT_INT;
}

void BytecodeGenerator::visitDoubleLiteralNode(DoubleLiteralNode *node)
{
    bytecode()->add(BC_DLOAD);
    bytecode()->addDouble(node->literal());

    _lastType = VT_DOUBLE;
}

uint16_t BytecodeGenerator::registerConstant(string const& constant) {
    return _code->makeStringConstant(constant);
}

void BytecodeGenerator::visitStringLiteralNode(StringLiteralNode *node) {
    uint16_t id = registerConstant(node->literal());
    bytecode()->add(BC_SLOAD);
    bytecode()->addUInt16(id);

    _lastType = VT_STRING;
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

    ScopeVarId scopeVarId = findScopeVarIdByName(var->name());

    uint16_t scopeId = scopeVarId.first;
    uint16_t varId = scopeVarId.second;

    AstNode* value = node->value();
    value->visit(this); // after this operation on TOS lies value which i must store
    VarType valueType = lastInferredType(); // resolveType(value);
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

//    _lastType = varType;
}

void BytecodeGenerator::visitLoadNode(LoadNode *node)
{
    const AstVar* var = node->var();
    ScopeVarId scopeVarId = findScopeVarIdByName(var->name());
    uint16_t scopeId = scopeVarId.first;
    uint16_t varId = scopeVarId.second;
    loadValueFromVar(scopeId, varId, var->type());

    _lastType = var->type();
}

void BytecodeGenerator::visitIfNode(IfNode *node) {

    AstNode* ifExpr = node->ifExpr();
    ifExpr->visit(this);
    VarType ifExprType = lastInferredType(); //resolveType(ifExpr);
    addCastToBool(ifExprType);

    Label lElse(bytecode());
    Label lEndIf(bytecode());

    bytecode()->add(BC_ILOAD0);
    bytecode()->addBranch(BC_IFICMPE, lElse);
//    bytecode()->add(BC_POP);
    //maybe add pop value of if expr
    BlockNode* thenBlock = node->thenBlock();
    thenBlock->visit(this);
    bytecode()->addBranch(BC_JA, lEndIf);

    bytecode()->bind(lElse);
//    bytecode()->add(BC_POP);
    //maybe add pop value of if expr
    BlockNode* elseBlock = node->elseBlock();
    if (elseBlock) {
        elseBlock->visit(this);
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

//    bytecode()->add(BC_POP);
    whileBlock->visit(this);

    bytecode()->addBranch(BC_JA, lBegin);
    bytecode()->bind(lEnd);
//    bytecode()->add(BC_POP);
}

//uint16_t BytecodeGenerator::getVarId(uint16_t scopeId, string const& name) {
//    VarMap& vars = _vars[scopeId];
//    for (VarMap::iterator varIt = vars.begin(); varIt != vars.end(); ++varIt) {
//        const string& varName = varIt->first->name();
//        if (varName == name) {
//            return varIt->second;
//        }
//    }

//    throw TranslationException();
//}

//std::pair<uint16_t, uint16_t> BytecodeGenerator::findScopeVarId(Scope* scope, const string& varName) {
//    while (scope != 0) {
//        uint16_t scopeId = _scopes[scope];
//        Scope::VarIterator varIt(scope);
//        while(varIt.hasNext()) {
//            AstVar* var = varIt.next();
//            if (var->name() == varName) {
//                uint16_t varId = getVarId(scopeId, varName);
//                return std::pair<uint16_t, uint16_t>(scopeId, varId);
//            }
//        }
//        scope = scope->parent();
//    }

//    throw TranslationException();
//}

//std::pair<uint16_t, uint16_t> BytecodeGenerator::findScopeVarId(const string &name) {
//    return findScopeVarId(currentScope(), name);
//}

void BytecodeGenerator::visitForNode(ForNode *node) {
    const AstVar* inVar = node->var();
    VarType inVarType = inVar->type();
    string inVarName = inVar->name();

    AstNode* inExpr = node->inExpr();
    inExpr->visit(this); // left on preTOS, right on TOS,
    VarType rangeType = lastInferredType(); //resolveType(inExpr);
    addCast(rangeType, inVarType);
    bytecode()->add(BC_SWAP);
    addCast(rangeType, inVarType); // left on TOS, right below

    BlockNode* forBlock = node->body();
//    Scope* forScope = forBlock->scope();
    uint16_t blockScopeId = currentFunctionTranslationContext()->getScopeId();

    ScopeVarId inScopeVarId = findScopeVarIdByName(inVarName);
    uint16_t scopeId = inScopeVarId.first;
    uint16_t inVarId = inScopeVarId.second;

    uint16_t leftRangeId = currentFunctionTranslationContext()->addVar("<left>");
    uint16_t rightRangeId = currentFunctionTranslationContext()->addVar("<right>");

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

    currentFunctionTranslationContext()->removeVarId("<left>");
    currentFunctionTranslationContext()->removeVarId("<right>");
}

//uint16_t BytecodeGenerator::translatedFunctionId() {
//    return _bcFunctionStack.back();
//}

void BytecodeGenerator::addReturn()
{
    bytecode()->add(BC_RETURN);
}

void BytecodeGenerator::addSwap()
{
    bytecode()->add(BC_SWAP);
}

void BytecodeGenerator::visitReturnNode(ReturnNode *node) {
    uint16_t id = currentFunctionTranslationContext()->getScopeId();  //translatedFunctionId();
    BytecodeFunction* bcFunction = dynamic_cast<BytecodeFunction*>(_code->functionById(id)); //  _bcFunctions[id];
    VarType targetReturnType = bcFunction->returnType();

    AstNode* returnExpr = node->returnExpr();
    if (returnExpr != NULL) {
        returnExpr->visit(this);
        VarType returnExprType = lastInferredType(); //resolveType(returnExpr);
        addCast(returnExprType, targetReturnType);
    }
    addReturn();

//    _lastType = targetReturnType;
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
        VarType operandType = lastInferredType(); //resolveType(operand);
        addPrint(operandType);
    }
}

void BytecodeGenerator::visitNativeCallNode(NativeCallNode *node) {
}

//AstFunction* BytecodeGenerator::getFunction(Scope* scope, const string& name) {
//    while(scope != 0) {
//        Scope::FunctionIterator functionIt(scope);
//        while(functionIt.hasNext()) {
//            AstFunction* astFunction = functionIt.next();
//            if (astFunction->name() == name) {
//                return astFunction;
//            }
//        }
//        scope = scope->parent();
//    }

//    throw TranslationException();
//}

//uint16_t BytecodeGenerator::getFunctionId(Scope* scope, const string& name) {
//    AstFunction* astFunction = getFunction(scope, name);
//    return _astFunctions[astFunction];
//}

void BytecodeGenerator::visitCallNode(CallNode *node) {
    uint16_t calleeId;

    if (isNative(node->name())) {
        calleeId = getNativeIdByName(node->name());
        const Signature* signature;
        const string* name;
        _code->nativeById(calleeId, &signature, &name);
        assert(signature->size() > 0);
        for (int i = signature->size() - 1; i > 0; --i) {
            AstNode* arg = node->parameterAt(i);
            arg->visit(this);
            VarType argType = lastInferredType(); //resolveType(arg);
            VarType paramType = signature->at(i).first;
            addCast(argType, paramType);
        }

        bytecode()->add(BC_CALLNATIVE);

        _lastType = signature->at(0).first;
    }
    else {
        calleeId = getFunctionIdByName(node->name());
        BytecodeFunction* bcFunction = dynamic_cast<BytecodeFunction*>(_code->functionById(calleeId));//_bcFunctions.at(calleeId);

        for (int i = node->parametersNumber() - 1; i > -1; --i) {
            AstNode* arg = node->parameterAt(i);
            arg->visit(this);
            VarType argType = lastInferredType(); //resolveType(arg);
            VarType paramType = bcFunction->parameterType(i);
            addCast(argType, paramType);
        }

        bytecode()->add(BC_CALL);

        _lastType = bcFunction->returnType();
    }

    bytecode()->addInt16(calleeId);
}

void BytecodeGenerator::visitBlockNode(BlockNode *node) {

    Scope* scope = node->scope();
    FunctionTranslationContext* context = currentFunctionTranslationContext();
    context->registerScopeVars(scope);
    registerScopeFunctions(scope);

    for (size_t i = 0; i < node->nodes(); ++i) {
        node->nodeAt(i)->visit(this);
    }

    translateScopeFunctions(scope);

    context->unregisterScopeVars(scope);
}

void BytecodeGenerator::registerScopeFunctions(Scope* scope) {
    Scope::FunctionIterator funcIt(scope);
    while(funcIt.hasNext()) {
        AstFunction* function = funcIt.next();
        if (function->node()->body()->nodeAt(0)->isNativeCallNode()) {
            registerNativeFunction(function->node()->body()->nodeAt(0)->asNativeCallNode());
        }
        else {
            registerFunction(function);
        }
    }

}

void BytecodeGenerator::registerNativeFunction(NativeCallNode* native) {
    uint16_t nativeId = _code->makeNativeFunction(native->nativeName(), native->nativeSignature(), NULL);
    _nativeIdByName[native->nativeName()] = nativeId;
}

void BytecodeGenerator::registerFunction(AstFunction *astFunction) {
    assert(_functionIdByName.find(astFunction->name()) == _functionIdByName.end());

    BytecodeFunction* bcFunction = new BytecodeFunction(astFunction);
    uint16_t bcFunctionId = _code->addFunction(bcFunction);

//    assert(bcFunctionId == _bcFunctions.size());
//    _bcFunctions.push_back(bcFunction);

    _functionIdByName[bcFunction->name()] = bcFunctionId;
}

void BytecodeGenerator::translateScopeFunctions(Scope *scope) {
    Scope::FunctionIterator funcIt(scope);
    while(funcIt.hasNext()) {
        AstFunction* function = funcIt.next();
        function->node()->visit(this);
    }
}

bool BytecodeGenerator::isNative(const string &name) {
    return _nativeIdByName.find(name) != _nativeIdByName.end();
}

uint16_t BytecodeGenerator::getNativeIdByName(const string &name) {
    assert(_nativeIdByName.find(name) != _nativeIdByName.end());
    return _nativeIdByName[name];
}

uint16_t BytecodeGenerator::getFunctionIdByName(const string &name) {
    assert(_functionIdByName.find(name) != _functionIdByName.end());
    return _functionIdByName[name];
}

/*
 * This FunctionNode contain really function, not native
*/
void BytecodeGenerator::collectArgs(FunctionNode *node) {
    for (size_t i = 0; i < node->parametersNumber(); ++i) {
        ScopeVarId scopeVarId = findScopeVarIdByName(node->parameterName(i));
        VarType type = node->parameterType(i);
        addStringIntDoubleInsn(type, BC_STORECTXSVAR, BC_STORECTXIVAR, BC_STORECTXDVAR);
        bytecode()->addUInt16(scopeVarId.first);
        bytecode()->addUInt16(scopeVarId.second);
    }
}

/*
 * Start translation of function with specified unique name
 * Function with specified name (unique!) must be already registered
*/
void BytecodeGenerator::visitFunctionNode(FunctionNode *node) { //this can contain NativeCallNode
    assert(_functionIdByName.find(node->name()) != _functionIdByName.end());

    if (isNative(node->name())) {
        return;
    }

    uint16_t functionId = _functionIdByName[node->name()];
    BytecodeFunction* bcFunction = dynamic_cast<BytecodeFunction*>(_code->functionById(functionId)); //_bcFunctions[functionId];
    bcFunction->setScopeId(functionId);
    _bytecodeStack.push_back(bcFunction->bytecode());

    FunctionTranslationContext* ftcontext = addNewFunctionTranslationContext(functionId);
    ftcontext->registerSignature(node->signature());

    collectArgs(node);
    node->body()->visit(this);

    ftcontext->unregisterSignature(node->signature());
    removeLastFunctionTranslationContext();
    _bytecodeStack.pop_back();
}

FunctionTranslationContext* BytecodeGenerator::addNewFunctionTranslationContext(uint16_t functionScopeId) {
    FunctionTranslationContext* context = new FunctionTranslationContext(functionScopeId);
    _contexts.push_back(context);

    return context;
}

void BytecodeGenerator::removeLastFunctionTranslationContext() {
    FunctionTranslationContext* context = _contexts.back();
    delete context;
    _contexts.pop_back();
}

FunctionTranslationContext* BytecodeGenerator::currentFunctionTranslationContext() {
    return _contexts.back();
}

ScopeVarId BytecodeGenerator::findScopeVarIdByName(const string &name) {
    for (std::vector<FunctionTranslationContext*>::reverse_iterator contextRevIt = _contexts.rbegin(); contextRevIt != _contexts.rend(); ++contextRevIt) {
        FunctionTranslationContext* context = *contextRevIt;
        if (context->varNameExist(name)) {
            return context->getScopeVarId(name);
        }
    }
    throw TranslationException("Couldn't find var with specified name");
}

//void BytecodeGenerator::visitAstFunction(AstFunction* astFunction) {
//    uint16_t id = registerFunction(astFunction);
//    BytecodeFunction* bcFunction = _bcFunctions[id];

//    FunctionNode* function = astFunction->node();
//    Scope* signatureScope = function->body()->scope()->parent();
//    registerScope(signatureScope);
//    Scope* bodyScope = function->body()->scope();
//    uint16_t bodyScopeId = registerScope(bodyScope);

//    bcFunction->setScopeId(bodyScopeId);

//    _bcFunctionStack.push_back(id);
//    _bytecodeStack.push_back(bcFunction->bytecode());

//    function->visit(this);

//    _bytecodeStack.pop_back();
//    _bcFunctionStack.pop_back();
//}

//uint16_t BytecodeGenerator::registerFunction(AstFunction* astFunction) {
//    if (_astFunctions.find(astFunction) != _astFunctions.end()) {
//        return _astFunctions[astFunction];
//    }
//    uint16_t id = _bcFunctions.size();
//    _astFunctions[astFunction] = id;
//    BytecodeFunction* bcFunction = new BytecodeFunction(astFunction);
//    //bcFunction->assignId(id);
//    _bcFunctions.push_back(bcFunction);

//    return id;
//}

//uint16_t BytecodeGenerator::registerVar(uint16_t scopeId, AstVar* var) {
//    VarMap& vars = _vars[scopeId];
//    uint16_t id = vars.size();
//    vars[var] = id;

//    return id;
//}

//uint16_t BytecodeGenerator::registerScope(Scope * scope) {
//    if (_scopes.find(scope) != _scopes.end()) {
//        return _scopes[scope];
//    }
//    uint16_t id = _scopes.size();
//    _scopes[scope] = id;

//    Scope::FunctionIterator functionIt(scope);
//    while(functionIt.hasNext()) {
//        AstFunction* astFunction = functionIt.next();
//        registerFunction(astFunction);
//    }

//    Scope::VarIterator varIt(scope);
//    while(varIt.hasNext()) {
//        AstVar* var = varIt.next();
//        registerVar(id, var);
//    }

//    functionIt = Scope::FunctionIterator(scope);
//    while(functionIt.hasNext()) {
//        AstFunction* astFunction = functionIt.next();
//        visitAstFunction(astFunction);
//    }

//    return id;
//}

//void FunctionScopeManager::registerScopeVars(Scope* scope)
//{
//    Scope::VarIterator varIt(scope);
//    while (varIt.hasNext()) {
//        AstVar* var = varIt.next;
//        VarNameIds& ids =
//    }
//}

void BytecodeGenerator::addCallTopFunction() {
    BytecodeFunction* top = dynamic_cast<BytecodeFunction*>(_code->functionByName("<top>"));
    top->bytecode()->add(BC_CALL);

    assert(top->id() == 0);
    top->bytecode()->addUInt16(top->id());
}

InterpreterCodeImpl* BytecodeGenerator::makeBytecode(AstFunction* top) {
    _code = new InterpreterCodeImpl();
    registerFunction(top);
//    addCallTopFunction();
    top->node()->visit(this);

//    for (std::vector<BytecodeFunction*>::const_iterator bcFunctionIt = _bcFunctions.begin(); bcFunctionIt != _bcFunctions.end(); ++bcFunctionIt) {
//        _code->addFunction(*bcFunctionIt);
//    }

    return _code;
}

}

// void *code = dlsym(RTLD_DEFAULT, node->nativeName().c_str());
