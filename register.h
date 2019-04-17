#ifndef REGISTER_H
#define REGISTER_H

#include <string>
#include <vector>
#include <map>

using namespace std;

class Register{
public:

    Register(string n, int val){name = n; value = val; }

    int getValue(){ return value; }
    string getName(){return name;}
    void setValue(int val){value = val;}

    void addDependency(string dep){
        dependencies.push_back(dep);
    }

private:
    int value; //value stored in this regster
    string name; //ie, "$t0", "$s0", etc
    vector<string> dependencies; //do we want to use a vector?
};

#endif