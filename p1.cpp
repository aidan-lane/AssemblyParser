/*
CompOrg Final Project 2019
By Aidan Lane, Tobias Park, Zach Koo, Yasmine Lu

Github link: https://github.com/aidan-lane/CompOrgProject
TODO:
 - Main cycle
 - Data Hazard
 - Forwarding
 - Control Hazard
 - Register printing
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

Instruction* parse_instruction(const string& line);
void print_registers(const REGISTER_MAP& r);

void simulate(const vector<Instruction*>& instructions, REGISTER_MAP& registers, bool forward);

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
    for(int i = 0;i<=7;i++) { 
        string reg = "$s" + to_string(i); 
        registers[reg] = new Register(0); 
    }
    for(int i = 0;i<=9;i++) {
        string reg = "$t" + to_string(i); 
        registers[reg] = new Register(0); 
    }

    //parse instructions from input files
    string line;
    while(getline(in, line)) {
        if(line[line.size() - 1] == '\r') line.erase(line.size()-1);
        instructions.push_back(parse_instruction(line));
    }

    //main cycle loop
    simulate(instructions, registers, forward);

    return EXIT_SUCCESS;
}

Instruction* parse_instruction(const string& line) {
    //parse operation; add, sub, beq, etc.
    int i = 0;
    string operation = "";
    while(line[i] != ' ') {
        operation += line[i];
        i++;
    }

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
    else {} //should be branch label
    
    instr->setRegisters(line);

    return instr;
}

void print_registers(const REGISTER_MAP& r) {
    int line_count = 1;
    for(REGISTER_MAP::const_iterator itr = r.begin(); itr != r.end(); ++itr) {
        if(itr->first.compare("$zero") == 0) itr++; //skip $zero
        string tmp = itr->first + " = " + to_string(itr->second->getValue());
        cout << left << setw(20) << tmp;
        if(line_count % 4 == 0) cout << "\n";
        line_count++;
    }
}

void simulate(const vector<Instruction*>& instructions, REGISTER_MAP& registers, bool forward) {
    cout << "START OF SIMULATION (" << (!forward ? "no " : "") << "forwarding)" << endl;
    cout << setfill('-') << setw(83);

    for(unsigned int cycle = 0; cycle < 16; cycle++) {
        cout << endl << setfill(' ') << left << setw(20) << "CPU CYCLES ===>";
        for(int i = 1; i <= 16; i++) cout << setfill(' ') << left << setw(4) << i;
        cout << endl;

        for(unsigned int i = 0; i <= cycle && i < instructions.size(); i++) {
            cout << left << setw(20) << instructions[i]->getLine();
            cout<<"TEST"<<endl;
        }

        cout << endl;
        print_registers(registers);
        
        cout << setfill('-') << setw(83) << "\n";
    }

    cout << endl << "END OF SIMULATION" << endl;
}