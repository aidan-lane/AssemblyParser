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
    Instruction() : stages(vector<string>(16, ".")), stage(0) {}

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

    //print the stages for this instruction
    void printStages(){
        for(unsigned int i=0; i<stages.size(); i++){
            cout << left << setw(4) << stages[i];
        }
        cout << endl;
    }

    //get last stage currently in stages vector so we know which one to add next
    string getLastStage(){
        bool foundStage = false;
        
        for(unsigned int i=0; i<stages.size(); i++){
            if(stages[i].compare(".") != 0) foundStage = true; //we found stages that are not periods
            if(foundStage && stages[i].compare(".") == 0) return stages[i-1]; //we've run into periods again; i-1 was last real stage
        }
        if(foundStage) return stages[stages.size()-1]; //corner case for if last real stage is also 16th stage
        return ""; //foundStage == false, there are no stages, return empty string
    }

    //add new stage to this isntruction
    void addStage(string s){
        stages[offset] = s;
        stage++;
        offset++;
    }

    int getStage(){
        return stage;
    }

    void setOffset(int o) {
        this->offset = o;
    }

protected:
    /* Instruction type denoted by its operation (add, beq, etc.)*/
    string type;
    string line; //actual complete instruction to be used for printing
    int offset; //how far away from starting from beginning (from cycle 1)
    int stage; //0-4 integer corresponding to stages (IF, ID, etc.)

    /* This instruction's registers: up to 3 (0-2)
        **immediate instructions must use stoi to parse int.
    */
    vector<string> regs;
    vector<string> stages; //IF, ID, etc.
};

#endif