#ifndef BYTECODEGENERATOR_H
#define BYTECODEGENERATOR_H

#include "mathvm.h"
#include "visitors.h"


namespace mathvm {

class TypeInferencer : public AstVisitor
{
    VarType _type;
    Scope* _scope;

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

    Bytecode* bytecode();
    inline Scope* currentScope();
    inline uint16_t currentScopeId();
    inline void setCurrentScope(Scope* scope);
    inline void setCurrentScopeId(uint16_t scopeId);

    void checkNumber(VarType type);


    typedef std::map<uint16_t, TranslatedFunction*> FunctionIdMap;

    typedef std::vector<string> vstr;
    typedef std::map<Scope*, uint16_t> ScopeMap;
    typedef std::map<AstVar*, uint16_t> VarMap;
    typedef std::map<uint16_t, VarMap> ScopeVarMap;

    typedef std::map<AstFunction*, uint16_t> AstFunctionMap;


    typedef std::map<std::string, uint16_t> NativeMap;
    typedef std::map<std::string, uint16_t> ConstantMap;

    uint16_t _currentScopeId;
    Scope* _currentScope;
    ScopeMap _scopes;
    ScopeVarMap _vars;

    AstFunctionMap _astFunctions;
    std::vector<BytecodeFunction*> _bcFunctions;
    std::vector<uint16_t> _bcFunctionStack;
    std::vector<Bytecode*> _bytecodeStack;

    NativeMap _nativeById;
    vector<NativeFunctionDescriptor> _natives;

    ConstantMap _constantById;
    std::vector<string> _constants;

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

    uint16_t translatedFunctionId();
    AstFunction* getFunction(Scope* scope, const string& name);
    uint16_t getFunctionId(Scope* scope, const string& name);
    uint16_t registerScope(Scope * scope);
    uint16_t registerFunction(AstFunction* astFunction);
    uint16_t registerVar(uint16_t scopeId, AstVar* var);
    uint16_t registerConstant(string const& constant);

    uint16_t getVarId(uint16_t scopeId, string const& name);
    std::pair<uint16_t, uint16_t> findScopeVarId(Scope* scope, string const& varName);
    std::pair<uint16_t, uint16_t> findScopeVarId(string const& varName);

public:
    BytecodeGenerator();
    virtual ~BytecodeGenerator();

    void visitAstFunction(AstFunction* astFunction);

#define VISITOR_FUNCTION(type, name) \
    virtual void visit##type(type* node);

    FOR_NODES(VISITOR_FUNCTION)
#undef VISITOR_FUNCTION
};

class TranslationException: public exception
{
    string _message;

public:
    TranslationException() {
    }

    virtual ~TranslationException() throw() {
    }

    TranslationException(string const& message)
        : _message(message) {
    }

    virtual const char* what() const throw() {
        return _message.c_str();
    }
};

}

#endif // BYTECODEGENERATOR_H
