#include "interpretercode.h"

namespace mathvm {

Stack::Stack()
    : _current(-1) {
}

void Stack::pushInt32(uint32_t i) {
    _elements.push_back(i);
}

void Stack::popElement() {
    _elements.pop_back();
    _types.pop_back();
}

void Stack::pushElement(element const& u) {
    _elements.push_back(u);
}

void Stack::pushInt32(uint32_t i) {
    _elements.push_back(i);
    _types.push_back(VT_INT);
}

uint32_t Stack::getInt32() {
    VarType type = _types.back();
    if (type != VT_INT) {
        throw InterpretationException();
    }

    return _elements.back().u;
}

}
