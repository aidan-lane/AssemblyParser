/*
CompOrg Final Project 2019
By Aidan Lane, Tobias Park,

Github link:
Main class (p1) 
 - parses input
*/

#include <iostream>
#include <cmath>
#include <string>
#include <vector>
#include <fstream>
#include <map>

#include "instructions.h"
#include "register.h"

using namespace std;

Instruction* parse_instruction(const string& line);

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

    //map of registers
    map<string, Register*> registers;

    //parse input file
    string line;
    while(getline(in, line)) {
        instructions.push_back(parse_instruction(line));
    }

    //main cycle loop
    int cycle = 0;

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
    else {}

    instr->setRegisters(line);

    return instr;
}