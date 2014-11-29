#ifndef BYTECODEGENERATOR_H
#define BYTECODEGENERATOR_H

#include "mathvm.h"
#include "visitors.h"
#include "interpretercode.h"
#include "exceptions.h"


namespace mathvm {

class TypeInferencer : public AstVisitor
{
    static const int ASSIGN_COUNT = 3;
    static const int COMPARE_COUNT = 9;
    static const int BIT_COUNT = 3;
    static const int ARIPHM_COUNT = 4;

    static const TokenKind assignOps[];//   = {tASSIGN, tINCRSET, tDECRSET};
    static const TokenKind compareOps[];// = {tEQ, tNEQ, tNOT, tLT, tLE, tGT, tGE, tOR, tAND};
    static const TokenKind bitOps[];//         = {tAOR, tAAND, tAXOR};
    static const TokenKind ariphmOps[];//   = {tADD, tSUB, tMUL, tDIV};

    VarType _type;
    Scope* _scope;

    VarType commonTypeForBinOp(TokenKind binOp, VarType left, VarType right) const;

    static bool find(TokenKind op, const TokenKind ops[], int count);
    bool isAssignmentOp(TokenKind binOp);
    bool isCompareOp(TokenKind binOp);
    bool isBitOp(TokenKind binOp);
    bool isAriphmOp(TokenKind binOp);

public:
    TypeInferencer();
    virtual ~TypeInferencer();

    void setScope(Scope* scope);
    VarType inferredType() const;
    VarType resolveType(AstNode* node);
    VarType commonType(VarType v1, VarType v2) const;

#define VISITOR_FUNCTION(type, name) \
    virtual void visit##type(type* node);

    FOR_NODES(VISITOR_FUNCTION)
#undef VISITOR_FUNCTION
};

typedef std::pair<uint16_t, uint16_t> ScopeVarId;

class FunctionTranslationContext
{
//    typedef std::pair<uint16_t, uint16_t> ScopeVarId;
    typedef std::vector<uint16_t> VarIds;
    typedef std::map<string, VarIds> VarNameToIdsMap;

    uint16_t _scopeId; // function scopeId

    VarNameToIdsMap _varNameToIds;
    uint16_t _freeVarId;

    uint16_t getFreeVarId();

    public:
    FunctionTranslationContext(uint16_t scopeId);

    void registerSignature(const Signature& signature);
    void registerScope(Scope* scope); // FOR and IF ELSE scopes
    void registerScopeVars(Scope* scope);
    void unregisterSignature(const Signature& signature);
    void unregisterScope(Scope* scope); // FOR and IF ELSE scopes
    void unregisterScopeVars(Scope* scope);

    uint16_t addVar(const string& name);
    void addVarId(const string& name, uint16_t id);
    void removeVarId(const string& name);

    bool varNameExist(const string& varName);
    uint16_t getVarId(const string& varName);
    uint16_t getScopeId();
    ScopeVarId getScopeVarId(const string& varName);

};

class BytecodeGenerator : public AstVisitor
{
    class BytecodeVar
    {
        uint16_t _scopeId;
        uint16_t _id;
        VarType _type;

    public:
        BytecodeVar(uint16_t scopeId, uint16_t id, VarType type)
            : _scopeId(scopeId), _id(id), _type(type) {
        }

        uint16_t scopeId() {
            return _scopeId;
        }

        uint16_t id() {
            return _id;
        }

        VarType type() {
            return _type;
        }
    };

    VarType _lastType;

    void storeValueToVar(uint16_t scopeId, uint16_t varId, VarType varType);
    void loadValueFromVar(uint16_t scopeId, uint16_t varId, VarType varType);

    void checkNumber(VarType type);


//    typedef std::map<uint16_t, TranslatedFunction*> FunctionIdMap;

//    typedef std::vector<string> vstr;
//    typedef std::vector<BytecodeFunction*> BytecodeFunctionVec;
//    typedef std::map<Scope*, uint16_t> ScopeMap;
//    typedef std::map<AstVar*, uint16_t> VarMap;
//    typedef std::map<uint16_t, VarMap> ScopeVarMap;

//    typedef std::map<AstFunction*, uint16_t> AstFunctionMap;


//    typedef std::vector<NativeFunctionDescriptor> NativeVec;
//    typedef std::map<std::string, uint16_t> NativeMap;


//    uint16_t _currentScopeId;
//    Scope* _currentScope;
//    ScopeMap _scopes;
//    ScopeVarMap _vars;

//    AstFunctionMap _astFunctions;
//    BytecodeFunctionVec _bcFunctions;
//    std::vector<uint16_t> _bcFunctionStack;


//    NativeMap _nativeById;
//    NativeVec _natives;

    TypeInferencer _typeInferencer;

    VarType resolveType(AstNode* node);
    VarType getCommonType(VarType type1, VarType type2);

    void addCast(VarType type, VarType targetType);

    void addIntDoubleInsn(VarType type, Instruction intInsn, Instruction doubleInsn);
    void addStringIntDoubleInsn(VarType type, Instruction stringInsn, Instruction intInsn, Instruction doubleInsn);

    void addNeg(VarType type);
    void addAdd(VarType type);
    void addSub(VarType type);
    void addMul(VarType type);
    void addDiv(VarType type);
    void addMod(VarType type);

    void addCastIntToBool();
    void addCastToBool(VarType type);
    void addCompareWith0andReplace(Instruction ifInsn,
                                   Instruction trueInsn,
                                   Instruction falseInsn);
    void addCastTwoLastToBool(VarType type);

    void addNot(VarType type);
    void addCompInsn(VarType type, Instruction insn);

    void addBitOpInsn(VarType type, Instruction insn);
    void addAOR(VarType type);
    void addAAND(VarType type);
    void addAXOR(VarType type);

    void addPrint(VarType type);
    void addReturn();

//    uint16_t translatedFunctionId();
//    AstFunction* getFunction(Scope* scope, const string& name);
//    uint16_t getFunctionId(Scope* scope, const string& name);
//    uint16_t registerScope(Scope * scope);
//    uint16_t registerFunction(AstFunction* astFunction);
//    uint16_t registerVar(uint16_t scopeId, AstVar* var);


//    uint16_t getVarId(uint16_t scopeId, string const& name);
//    std::pair<uint16_t, uint16_t> findScopeVarId(Scope* scope, string const& varName);
//    std::pair<uint16_t, uint16_t> findScopeVarId(string const& varName);

    InterpreterCodeImpl* _code;

    ///////////////////=========

    typedef std::map<std::string, uint16_t> ConstantMap;
    ConstantMap _constantById;
    std::vector<string> _constants;
    uint16_t registerConstant(string const& constant);

    typedef std::map<string, uint16_t> FunctionNameToIdMap;
    FunctionNameToIdMap _functionIdByName;
    FunctionNameToIdMap _nativeIdByName;
    std::vector<BytecodeFunction*> _bcFunctions;
    std::vector<NativeFunctionDescriptor> _natives;

    std::vector<Bytecode*> _bytecodeStack;
    Bytecode* bytecode();

    bool isNative(const string& name);
    uint16_t getNativeIdByName(const string& name);
    uint16_t getFunctionIdByName(const string& name);
    void registerScopeFunctions(Scope* scope);
    void registerNativeFunction(NativeCallNode* native);
    void registerFunction(AstFunction *astFunction);

    void collectArgs(FunctionNode* node);
    void translateScopeFunctions(Scope* scope);

    std::vector<FunctionTranslationContext*> _contexts;
    FunctionTranslationContext* addNewFunctionTranslationContext(uint16_t functionScopeId);
    void removeLastFunctionTranslationContext();
    FunctionTranslationContext* currentFunctionTranslationContext();

    ScopeVarId findScopeVarIdByName(const string& name);

public:
    BytecodeGenerator();
    virtual ~BytecodeGenerator();

    InterpreterCodeImpl* makeBytecode(AstFunction* top);
//    void visitAstFunction(AstFunction* astFunction);

#define VISITOR_FUNCTION(type, name) \
    virtual void visit##type(type* node);

    FOR_NODES(VISITOR_FUNCTION)
#undef VISITOR_FUNCTION
};

}

#endif // BYTECODEGENERATOR_H
