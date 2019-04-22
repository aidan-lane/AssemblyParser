#ifndef REGISTER_H
#define REGISTER_H

#include <string>
#include <vector>
#include <map>

using namespace std;

class Register {
public:

    Register(int val = 0) : value(val), used(false) {}

    int getValue() { return value; }
    void setValue(int val) { value = val; }
    void setUsed(bool b, int line) { used = b; last = line; }
    bool isUsed() { return used; }

    int getLastUsedLine() { return last; }

private:
    int value; //value stored in this regster
    bool used;

    int last;
};

#endif