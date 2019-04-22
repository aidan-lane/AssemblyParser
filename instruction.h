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
protected:
    vector<string> stages; //IF, ID, etc. Declared here to avoid compiler warnings.

public:
    //constructor, initializing the values in the vector stages and setting integer stage to 0
    Instruction() : stages(vector<string>(16, ".")) {
        regs.push_back(""); regs.push_back(""); regs.push_back("");
        stage = 0;
        line = "nop";
    }

    void setType(const string& t) {type  = t;}
    const string& getType() {return type;}
    const string& getLine() {return line; }

    /*
    @param registers: map of current global/temporary register's values
    */
    virtual bool operate(REGISTER_MAP& registers) = 0;

    /*
    gets registers/labels/immediates and adds to vector
    @param line: instruction line to retrieve data from
    */
    void setRegisters(const string& line) {
        if(type.compare("nop") == 0) return;

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

    //print the stages for this instruction
    void printStages(){
        for(unsigned int i=0; i<stages.size(); i++){
            if(i != stages.size()-1) cout << left << setw(4) << stages[i];
            else cout << left << stages[i];
        }
        cout << endl;
    }

    //increasing the value of nop
    void incrementNop(){
        nops++;
    }

    //returning nop
    int getNop(){
        return nops;
    }
    
    // add new stage to this instruction
    void addStage(string s) {
        if (halted)
            stages[offset+stage+nops] = "*";
        else
            stages[offset+stage+nops] = s;
        stage++;
    }

    //returns current stage as an int
    int getStage(){
        return stage;
    }

    //sets the current offset
    void setOffset(int o) {
        offset = o;
    }

    //returns current offset
    int getOffset() {
        return offset;
    }
    
    //decrements stage for when isUsed is true
    void decrementStage(){
        stage--;
    }

    /* check whether 2nd or 3rd registers are used (for data hazards) */
    pair<bool,int> isUsed(REGISTER_MAP& rm) {
        REGISTER_MAP::iterator itr = rm.find(regs[2]); //used to check if last thing is an integer
        
        if(itr == rm.end() && regs[1].compare("$zero") == 0) return make_pair(false, 0);
        if(regs[1].compare("$zero") == 0 && regs[2].compare("$zero") == 0) return make_pair(false, 0);

        if(rm[regs[1]]->isUsed() && itr != rm.end() && rm[regs[2]]->isUsed())
            return make_pair(true, offset-rm[regs[2]]->getLastUsedLine());
        else if(rm[regs[1]]->isUsed())
            return make_pair(true, offset-rm[regs[1]]->getLastUsedLine());
        else if(itr != rm.end() && rm[regs[2]]->isUsed())
            return make_pair(true, offset-rm[regs[2]]->getLastUsedLine());

        return make_pair(false, 0);
    }

    //returns whatever element in regs that is at index (0-2)
    string getRegister(int index) {
        return regs[index];
    }

protected:
    /* Instruction type denoted by its operation (add, beq, etc.)*/
    string type;
    string line; //actual complete instruction to be used for printing
    int offset; //how far away from starting from beginning (from cycle 1)
    int stage; //0-4 integer corresponding to stages (IF, ID, etc.)

    int nops = 0;
    bool halted = false; //will be true if this instruction was halted after a branch

    /* This instruction's registers: up to 3 (0-2)
        **immediate instructions must use stoi to parse int.
    */
    vector<string> regs;
};

#endif