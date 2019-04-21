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

#define REGISTER_MAP map<string, Register*>

using namespace std;

class Instruction {
public:
    Instruction() {}

    void setType(const string& t) {type  = t;}
    const string& getType() {return type;}
    const string& getLine() { return line; }

    /*
    @param registers: map of current global/temporary register's values
    */
    virtual void operate(REGISTER_MAP& registers) = 0;

    /*
    gets registers/labels/immediates and adds to vector
    @param line: instruction line to retrieve data from
    */
    void setRegisters(const string& line) {
        regs.push_back(""); regs.push_back(""); regs.push_back("");
        int current = line.find_first_of(" ") + 1;
        int tmp = 0;

        while(current < (int) line.length()) {
            if(line[current] == ',') tmp++;
            else {
                regs[tmp] += line[current];
            }
            current++;
        }
        this->line = line;
    }

    /* Helper temporary function for debugging*/
    void printRegisters() {
        for(unsigned int i = 0;i<regs.size();i++) {
            cout << regs[i] << endl;
        }
    }

protected:
    /* Instruction type denoted by its operation (add, beq, etc.)*/
    string type;
    string line; //actual complete instruction to be used for printing

    /* This instruction's registers: up to 3 (0-2)
        **immediate instructions must use stoi to parse int.
    */
    vector<string> regs;
};

#endif