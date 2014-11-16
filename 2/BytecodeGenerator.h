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
    VarType resolveType(const VarType v1, const VarType v2) const;

#define VISITOR_FUNCTION(type, name) \
    virtual void visit##type(type* node);

    FOR_NODES(VISITOR_FUNCTION)
#undef VISITOR_FUNCTION
};

class BytecodeGenerator : public AstVisitor
{
    Bytecode _bytecode;
    TypeInferencer _typeInferencer;

public:
    BytecodeGenerator();
    virtual ~BytecodeGenerator();

#define VISITOR_FUNCTION(type, name) \
    virtual void visit##type(type* node);

    FOR_NODES(VISITOR_FUNCTION)
#undef VISITOR_FUNCTION
};

}

#endif // BYTECODEGENERATOR_H
