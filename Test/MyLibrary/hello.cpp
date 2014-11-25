#include <iostream>

using namespace std;

extern "C" void hello() {
    cout << "hello!" << endl;
}
