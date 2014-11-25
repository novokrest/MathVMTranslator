#ifndef CONTEXTMANAGER_H
#define CONTEXTMANAGER_H

#include "mathvm.h"

namespace mathvm {

class VarValue
{
    union {
        double d;
        uint32_t i;
        uint16_t id;
    } _value;

    VarType _type;

public:
    VarValue();
    VarValue(double d);
    VarValue(int32_t i);
    VarValue(uint16_t id);

    VarType type();

    double doubleValue();
    int32_t intValue();
    uint16_t stringIdValue();

    void setDouble(double d);
    void setInt(int32_t i);
    void setStringId(uint16_t id);
};

class InterpreterStack
{
    vector<VarValue> _elements;
    uint32_t _current;

public:
    void pushDouble(double d);
    void pushInt(int32_t i);
    void pushStringId(uint16_t id);

    VarValue getElement();
    double getDouble();
    int32_t getInt();
    uint16_t getStringId();

    void popElement();
    double popDouble();
    int32_t popInt();
    uint16_t popStringId();
};

class ContextManager
{
    typedef std::map<uint16_t, VarValue> Context;
    typedef std::vector<Context> RecursiveContextVec;
    typedef std::map<uint16_t, RecursiveContextVec> ContextMap;// -> ContextVec

    ContextMap _contextById;
    uint16_t _currentContextId;

    void checkContext(uint16_t contextId);
    void checkCtxVar(uint16_t contextId, uint16_t varId);

public:
    Context& getContext(uint16_t contextId);
    void addContext(uint16_t contextId);
    void removeContext(uint16_t contextId);

    void setCurrentContextId(uint16_t contextId);
    uint16_t getCurrentContextId();

    double loadDoubleFromCtxVar(uint16_t contextId, uint16_t varId);
    double loadDoubleFromVar(uint16_t varId);
    int32_t loadIntFromCtxVar(uint16_t contextId, uint16_t varId);
    int32_t loadIntFromVar(uint16_t varId);
    uint16_t loadStringFromCtxVar(uint16_t contextId, uint16_t varId);
    uint16_t loadStringFromVar(uint16_t varId);

    void storeDoubleToCtxVar(uint16_t contextId, uint16_t varId, double dvalue);
    void storeDoubleToVar(uint16_t varId, double dvalue);
    void storeIntToCtxVar(uint16_t contextId, uint16_t varId, int32_t ivalue);
    void storeIntToVar(uint16_t varId, int32_t ivalue);
    void storeStringToCtxVar(uint16_t contextId, uint16_t varId, uint16_t svalue);
    void storeStringToVar(uint16_t varId, uint16_t svalue);
};


}


#endif // CONTEXTMANAGER_H
