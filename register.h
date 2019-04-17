#ifndef REGISTER_H
#define REGISTER_H

#include <string>
#include <vector>
#include <map>

using namespace std;

class Register {
public:

    Register(string n, int val) { name = n; value = val; used = false; }

    int getValue() { return value; }
    string getName() { return name; }
    void setValue(int val) { value = val; }
    void setUsed(bool b) { used = b; }
    bool isUsed() { return used; }

private:
    int value; //value stored in this regster
    string name; //ie, "$t0", "$s0", etc
    bool used;
};

#endif