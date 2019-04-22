#ifndef INSTRUCTIONS_H
#define INSTRUCTIONS_H

#include "instruction.h"

class Add : public Instruction {
public:
    Add(const string& t) { setType(t); }
    bool operate(REGISTER_MAP& rm) {
        rm[regs[0]]->setValue(rm[regs[1]]->getValue() + rm[regs[2]]->getValue());
        return false;
    }
};

class Addi : public Instruction {
public:
    Addi(const string& t) { setType(t); }
    bool operate(REGISTER_MAP& rm) {
        rm[regs[0]]->setValue(rm[regs[1]]->getValue() + stoi(regs[2]));
        return false;
    }
};

class And : public Instruction {
public:
    And(const string& t) { setType(t); }
    bool operate(REGISTER_MAP& rm) {
        rm[regs[0]]->setValue(rm[regs[1]]->getValue() & rm[regs[2]]->getValue());
        return false;
    }
};

class Andi : public Instruction {
public:
    Andi(const string& t) { setType(t); }
    bool operate(REGISTER_MAP& rm) {
        rm[regs[0]]->setValue(rm[regs[1]]->getValue() & stoi(regs[2]));
        return false;
    }
};

class Or : public Instruction {
public:
    Or(const string& t) { setType(t); }
    bool operate(REGISTER_MAP& rm) {
        rm[regs[0]]->setValue(rm[regs[1]]->getValue() | rm[regs[2]]->getValue());
        return false;
    }
};

class Ori : public Instruction {
public:
    Ori(const string& t) { setType(t); }
    bool operate(REGISTER_MAP& rm) {
        rm[regs[0]]->setValue(rm[regs[1]]->getValue() | stoi(regs[2]));
        return false;
    }
};

class Slt : public Instruction {
public:
    Slt(const string& t) { setType(t); }
    bool operate(REGISTER_MAP& rm) {
        int s = rm[regs[1]]->getValue() < rm[regs[2]]->getValue() ? 1 : 0;
        rm[regs[0]]->setValue(s);
        return false;
    }
};

class Slti : public Instruction {
public:
    Slti(const string& t) { setType(t); }
    bool operate(REGISTER_MAP& rm) {
        int s = rm[regs[1]]->getValue() < stoi(regs[2]) ? 1 : 0;
        rm[regs[0]]->setValue(s);
        return false;
    }
};

//return true if theres a branch
class Beq : public Instruction {
public:
    Beq(const string& t) { setType(t); }
    bool operate(REGISTER_MAP& rm) {
        return rm[regs[0]] == rm[regs[1]];
    }
};

class Bne : public Instruction {
public:
    Bne(const string& t) { setType(t); }
    bool operate(REGISTER_MAP& rm) {
        return !(rm[regs[0]] == rm[regs[1]]);
    }
};

class Nop : public Instruction {
public:
    Nop(const string& t) { setType(t); }
    bool operate(REGISTER_MAP& rm) { return false; } //has to inherit this function, no use
};

#endif