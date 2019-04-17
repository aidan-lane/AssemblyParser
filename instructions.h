#ifndef INSTRUCTIONS_H
#define INSTRUCTIONS_H

#include "instruction.h"

class Add : public Instruction {
public:
    Add(const string& t) { setType(t); }
    void operate(map<string, int>& rm) {
        rm[regs[0]] = rm[regs[1]] + rm[regs[2]];
    }
};

class Addi : public Instruction {
public:
    Addi(const string& t) { setType(t); }
    void operate(map<string, int>& rm) {
        rm[regs[0]] = rm[regs[1]] + stoi(regs[2]);
    }
};

class And : public Instruction {
public:
    And(const string& t) { setType(t); }
    void operate(map<string, int>& rm) {
        rm[regs[0]] = rm[regs[1]] & rm[regs[2]];
    }
};

class Andi : public Instruction {
public:
    Andi(const string& t) { setType(t); }
    void operate(map<string, int>& rm) {
        rm[regs[0]] = rm[regs[1]] & stoi(regs[2]);
    }
};

class Or : public Instruction {
public:
    Or(const string& t) { setType(t); }
    void operate(map<string, int>& rm) {
        rm[regs[0]] = rm[regs[1]] | rm[regs[2]];
    }
};

class Ori : public Instruction {
public:
    Ori(const string& t) { setType(t); }
    void operate(map<string, int>& rm) {
        rm[regs[0]] = rm[regs[1]] | stoi(regs[2]);
    }
};

class Slt : public Instruction {
public:
    Slt(const string& t) { setType(t); }
    void operate(map<string, int>& rm) {
        rm[regs[0]] = (rm[regs[1]] < rm[regs[2]]) ? 1 : 0;
    }
};

class Slti : public Instruction {
public:
    Slti(const string& t) { setType(t); }
    void operate(map<string, int>& rm) {
        rm[regs[0]] = (rm[regs[1]] < stoi(regs[2])) ? 1 : 0;
    }
};

#endif