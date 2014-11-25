#ifndef UNION_TEST_H
#define UNION_TEST_H

#include <vector>

using std::vector;

class Stack
{
    union element {
        double d;
        uint32_t i;
        uint32_t id;
    };

    vector<element> _elements;
    uint32_t _current;

public:
    void addInt32(uint32_t i) {
        element u;
        u.d = 10.0;
        _elements.push_back(u);
    }

    void addDouble(double d);
    void addString(uint32_t id);

    uint32_t getInt32() {
        return _elements.back().i;
    }

    double getDouble();
    string getString();
};

#endif // UNION_TEST_H
