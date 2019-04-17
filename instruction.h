#ifndef INSTRUCTION_H
#define INSTRUCTION_H

/*
Abstract class instruction
Template for all operations (add, beq, etc.)
*/

#include <string>
#include <vector>
#include <map>
#include "register.h"

using namespace std;

class Instruction {
public:
    virtual ~Instruction() = 0;

    void setType(const string& t) {type  = t;}
    const string& getType() {return type;}

    /*
    @param registers: map of current global/temporary register's values
    */
    virtual void operate(map<string, int>& registers);

    /*
    gets registers/labels/immediates and adds to vector
    @param line: instruction line to retrieve data from
    */
    void setRegisters(const string& line) {
        int current = line.find_first_of(" ") + 1;
        int tmp = 0;
        while(current < (int) line.length()) {
            if(line[current] == ',') tmp++;
            else {
                regs[tmp] += line[current];
            }
            current++;
        }
    }

protected:
    /* Instruction type denoted by its operation (add, beq, etc.)*/
    string type;

    /* This instruction's registers: up to 3 (0-2)
        **immediate instructions must use stoi to parse int.
    */
    vector<string> regs;
};

#endif