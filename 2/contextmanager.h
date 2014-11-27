#ifndef CONTEXTMANAGER_H
#define CONTEXTMANAGER_H

#include "mathvm.h"
#include "exceptions.h"

namespace mathvm {

class VarValue
{
    union {
        double d;
        uint64_t i;
        uint16_t id;
    } _value;

    VarType _type;

public:
    VarValue();
    VarValue(double d);
    VarValue(int64_t i);
    VarValue(uint16_t id);

    VarType type();

    double doubleValue();
    int64_t intValue();
    uint16_t stringIdValue();

    void setDouble(double d);
    void setInt(int64_t i);
    void setStringId(uint16_t id);
};

class InterpreterStack
{
    vector<VarValue> _elements;
    uint64_t _current;

public:
    void pushElement(VarValue element);
    void pushDouble(double d);
    void pushInt(int64_t i);
    void pushStringId(uint16_t id);

    VarValue getElement();
    double getDouble();
    int64_t getInt();
    uint16_t getStringId();

    VarValue popElement();
    double popDouble();
    int64_t popInt();
    uint16_t popStringId();

    void swapTwoUpperElements();
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
    int64_t loadIntFromCtxVar(uint16_t contextId, uint16_t varId);
    int64_t loadIntFromVar(uint16_t varId);
    uint16_t loadStringIdFromCtxVar(uint16_t contextId, uint16_t varId);
    uint16_t loadStringIdFromVar(uint16_t varId);

    void storeDoubleToCtxVar(uint16_t contextId, uint16_t varId, double dvalue);
    void storeDoubleToVar(uint16_t varId, double dvalue);
    void storeIntToCtxVar(uint16_t contextId, uint16_t varId, int64_t ivalue);
    void storeIntToVar(uint16_t varId, int64_t ivalue);
    void storeStringIdToCtxVar(uint16_t contextId, uint16_t varId, uint16_t svalue);
    void storeStringIdToVar(uint16_t varId, uint16_t svalue);
};


}


#endif // CONTEXTMANAGER_H
