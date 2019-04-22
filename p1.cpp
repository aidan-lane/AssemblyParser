/*
CompOrg Final Project 2019
By Aidan Lane, Tobias Park, Zach Koo, Yasmine Lu

Github link: https://github.com/aidan-lane/CompOrgProject
TODO:
 - Data Hazard w/out forwarding
 - Data hazard w/ Forwarding (just don't do anything lol)
 - Control Hazard - assume that we don't branch; as soon as the dependency variables are available, check, and if we did branch, kill the old instructions and fix things
*/

#include <iostream>
#include <cmath>
#include <string>
#include <vector>
#include <fstream>
#include <map>
#include <iomanip>
#include <stdlib.h>

#include "instructions.h"
#include "register.h"

using namespace std;

Instruction* parse_instruction(const string& line, int& offset, map<string, int>& labels);
void print_registers(const REGISTER_MAP& r);

void simulate(vector<Instruction*>& instructions, REGISTER_MAP& registers, const map<string, int>& labels, bool forward);

int get_nops_before(vector<Instruction*>& instructions, int index);

int main(int argc, char** argv) {

    //check for correct # of arguments (3)
    if(argc < 3) {
        cout << "Invalid number of arguments" << endl;
        return EXIT_FAILURE;
    }

    //arg[1]; forwarding or non-forwarding
    string arg1 = argv[1];
    bool forward = (arg1.compare("F") == 0) ? true : false;

    //arg[2] is input file; read
    ifstream in(argv[2]);

    //command vector
    vector<Instruction*> instructions;

    //map of registers and init
    REGISTER_MAP registers;
    registers["$zero"] = new Register(0);
    for(int i = 0;i<=7;i++) { 
        string reg = "$s" + to_string(i); 
        registers[reg] = new Register(0); 
    }
    for(int i = 0;i<=9;i++) {
        string reg = "$t" + to_string(i); 
        registers[reg] = new Register(0); 
    }

    //map of labels to offsets
    map<string, int> labels; 

    //parse instructions from input files
    string line;
    int offset = 0;
    while(getline(in, line)) {
        if(line[line.size() - 1] == '\r') line.erase(line.size()-1); //fix weird C++ quirk
        instructions.push_back(parse_instruction(line, offset, labels));
    }

    //main cycle loop
    simulate(instructions, registers, labels, forward);

    return EXIT_SUCCESS;
}

Instruction* parse_instruction(const string& line, int& offset, map<string, int>& labels) {
    //parse operation; add, sub, beq, etc.
    int i = 0;
    string operation = "";
    while(line[i] != ' ') {
        operation += line[i];
        i++;
    }

    bool is_label = false; 

    Instruction* instr;

    if(operation.compare("add") == 0)       instr = new Add("add");
    else if(operation.compare("addi") == 0) instr = new Addi("addi");
    else if(operation.compare("and") == 0)  instr = new And("and");
    else if(operation.compare("andi") == 0) instr = new Andi("andi");
    else if(operation.compare("or") == 0)   instr = new Or("or");
    else if(operation.compare("ori") == 0)  instr = new Ori("ori");
    else if(operation.compare("slt") == 0)  instr = new Slt("slt");
    else if(operation.compare("slti") == 0) instr = new Slti("slti");
    else if(operation.compare("beq") == 0)  0; //wip
    else if(operation.compare("bne") == 0)  0; //wip
    else {
        is_label = true;
    }

    instr->setOffset(offset);
    offset++;

    instr->setRegisters(line);

    //if line is a jump label, set its location to that of instruction that appears after it
    if(is_label) {
        labels[line] = offset; 
        offset--;
    }

    return instr;
}

void print_registers(const REGISTER_MAP& r) {
    int line_count = 1;
    for(REGISTER_MAP::const_iterator itr = r.begin(); itr != r.end(); ++itr) {
        if(itr->first.compare("$zero") == 0) continue;
        string tmp = itr->first + " = " + to_string(itr->second->getValue());
        cout << left << setw(20) << tmp;
        if(line_count % 4 == 0) cout << "\n";
        line_count++;
    }
}

void simulate(vector<Instruction*>& instructions, REGISTER_MAP& registers, const map<string, int>& labels, bool forward) {
    cout << "START OF SIMULATION (" << (!forward ? "no " : "") << "forwarding)" << endl;
    cout << setfill('-') << setw(83);

    for(unsigned int cycle = 0; cycle < 16 && instructions[instructions.size()-1]->getStage() < 5; cycle++) {
        cout << endl << setfill(' ') << left << setw(20) << "CPU CYCLES ===>";
        
        //print the numbers for the top "CPU Cycles" line
        for(int i = 1; i <= 16; i++) cout << setfill(' ') << left << setw(4) << i;
        cout << endl;  

        //loop through each instruction, print stages
        for(unsigned int i = 0; i <= cycle && i < instructions.size(); i++) {
            cout << left << setw(20) << instructions[i]->getLine(); //print MIPS instruction

            //skip logic on any added "nop" lines
            if(instructions[i]->getType().compare("nop") == 0) goto skip;

            if(instructions[i]->getStage() == 0) {
                instructions[i]->addStage("IF");
                registers[instructions[i]->getRegister(0)]->setUsed(true, instructions[i]->getOffset());
            }
            else if (instructions[i]->getStage() == 1){
                instructions[i]->addStage("ID");
            }
            else if (instructions[i]->getStage() == 2){
                instructions[i]->addStage("EX");
            }
            else if (instructions[i]->getStage() == 3){
                instructions[i]->addStage("MEM");
            }
            else if (instructions[i]->getStage() == 4){
                instructions[i]->addStage("WB");
                instructions[i]->operate(registers);
                registers[instructions[i]->getRegister(0)]->setUsed(false, 0);
            }
skip:
            //incrementing nop stage
            if(instructions[i]->getType().compare("nop") == 0) {
                if(instructions[i]->getStage() < 5) instructions[i]->addStage("*");
            }
            instructions[i]->printStages(); 
        }

        cout << endl;
        print_registers(registers);
        
        cout << setfill('-') << setw(83) << "\n";
    }

    cout << endl << "END OF SIMULATION" << endl;
}

int get_nops_before(vector<Instruction*>& instructions, int index) {
    if(index == 0) return 0;
    int total = 0;
    for(int i = index;i>=0;i--) {
        if(instructions[i]->getType().compare("nop") == 0) {
            total++;
        }
        if(i < index - 2) break;
    }
    return total;
}