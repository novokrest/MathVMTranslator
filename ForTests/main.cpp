#include <iostream>
#include <vector>
#include <map>

using namespace std;

class VarValue
{
    union {
        double d;
        int64_t i;
        uint16_t id;
    } _value;
};

int fib(int x) {
    if (x == 0) {
        return 0;
    }
    fib(x - 1);

    return x * 2;
}

int main()
{
    map<uint16_t, VarValue> myMap;
    myMap[1] = VarValue();

    vector< map<uint16_t, VarValue> > myVec;

    for (size_t i = 0; i < 100000; ++i) {
        myVec.push_back(myMap);
    }

    fib(100000);

    int j = 5 % 0;

    return 0;
}

