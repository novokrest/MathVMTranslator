#include "contextmanager.h"


namespace mathvm {

class InterpretationException;

VarValue::VarValue()
    :_type(VT_INVALID) {
}

VarValue::VarValue(double d)
    : _type(VT_DOUBLE) {
    _value.d = d;
}

VarValue::VarValue(int32_t i)
    : _type(VT_INT) {
    _value.i = i;
}

VarValue::VarValue(uint16_t id)
    : _type(VT_STRING) {
    _value.id = id;
}

VarType VarValue::type() {
    return _type;
}

double VarValue::doubleValue() {
    assert(_type == VT_DOUBLE);
    return _value.d;
}

int32_t VarValue::intValue() {
    assert(_type == VT_INT);
    return _value.i;
}

uint16_t VarValue::stringIdValue() {
    assert(_type == VT_STRING);
    return _value.id;
}

void VarValue::setDouble(double d) {
    _type = VT_DOUBLE;
    _value.d = d;
}

void VarValue::setInt(int32_t i) {
    _type = VT_INT;
    _value.i = i;
}

void VarValue::setStringId(uint16_t id) {
    _type = VT_STRING;
    _value.id = id;
}

void InterpreterStack::pushDouble(double d) {
    _elements.push_back(VarValue(d));
}

void InterpreterStack::pushInt(int32_t i) {
    _elements.push_back(VarValue(i));
}

void InterpreterStack::pushStringId(uint16_t id) {
    _elements.push_back(VarValue(id));
}

VarValue& InterpreterStack::getElement() {
    return _elements.back();
}

double InterpreterStack::getDouble() {
    return _elements.back().doubleValue();
}

int32_t InterpreterStack::getInt() {
    return _elements.back().intValue();
}

uint16_t InterpreterStack::getStringId() {
    return _elements.back().stringIdValue();
}

void InterpreterStack::popElement() {
    _elements.pop_back();
}

double InterpreterStack::popDouble() {
    double d = getDouble();
    popElement();

    return d;
}

int32_t InterpreterStack::popInt() {
    int32_t i = getInt();
    popElement();

    return i;
}

uint16_t InterpreterStack::popStringId() {
    uint16_t id = getStringId();
    popElement();

    return id;
}

void ContextManager::checkContext(uint16_t contextId) {
    ContextMap::iterator contextIt = _contextById.find(contextId);
    if (contextIt == _contextById.end()) {
        throw InterpretationException("from ContextManager::checkContext()");
    }
}

void ContextManager::checkCtxVar(uint16_t contextId, uint16_t varId) {
    Context& context = getContext(contextId);
    Context::iterator varIt = context.find(varId);
    if (varIt == context.end()) {
        throw InterpretationException();
    }
}

Context& ContextManager::getContext(uint16_t contextId) {
    checkContext(contextId);
    return _contextById[contextId].back();
}

void ContextManager::addContext(uint16_t contextId) {
    _contextById[contextId].push_back(Context());
}

void ContextManager::removeContext(uint16_t contextId) {
    checkContext(contextId);
    _contextById[contextId].pop_back();
    if (_contextById.at(contextId).size() == 0) {
        _contextById.erase(contextId);
    }
}

void ContextManager::setCurrentContextId(uint16_t contextId) {
    _contextById = contextId;
}

uint16_t ContextManager::getCurrentContextId() {
    return _currentContextId;
}

double ContextManager::loadDoubleFromCtxVar(uint16_t contextId, uint16_t varId) {
    checkCtxVar(contextId, varId);
    return getContext(contextId).doubleValue();
}

double ContextManager::loadDoubleFromVar(uint16_t varId) {
    return loadDoubleFromCtxVar(getCurrentContextId(), varId);
}

int32_t ContextManager::loadIntFromCtxVar(uint16_t contextId, uint16_t varId) {
    checkCtxVar(contextId, varId);
    return getContext(contextId).intValue();
}

int32_t ContextManager::loadIntFromVar(uint16_t varId) {
    return loadIntFromCtxVar(getCurrentContextId(), varId);
}

uint16_t ContextManager::loadStringFromCtxVar(uint16_t contextId, uint16_t varId) {
    checkCtxVar(contextId, varId);
    return getContext(contextId).stringIdValue();
}

uint16_t ContextManager::loadStringFromVar(uint16_t varId) {
    return loadStringFromCtxVar(getCurrentContextId(), varId);
}

void ContextManager::storeDoubleToCtxVar(uint16_t contextId, uint16_t varId, double dvalue) {
    Context& context = getContext(contextId);
    context[varId].setDouble(dvalue);
}

void ContextManager::storeDoubleToVar(uint16_t varId, double dvalue) {
    storeDoubleToCtxVar(getCurrentContextId(), varId, dvalue);
}

void ContextManager::storeIntToCtxVar(uint16_t contextId, uint16_t varId, int32_t ivalue) {
    Context& context = getContext(contextId);
    context[varId].setInt(ivalue);
}

void ContextManager::storeIntToVar(uint16_t varId, int32_t ivalue) {
    storeIntToCtxVar(getCurrentContextId(), varId, ivalue);
}

void ContextManager::storeStringToCtxVar(uint16_t contextId, uint16_t varId, uint16_t svalue) {
    Context& context = getContext(contextId);
    context[varId].setStringId(svalue);
}

void ContextManager::storeStringToVar(uint16_t varId, uint16_t svalue) {
    storeStringToCtxVar(getCurrentContextId(), varId, svalue);
}

}
