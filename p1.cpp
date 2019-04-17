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
    map<string, int> registers;
    //initialize all registers to 0
    for(int i = 0;i<=7;i++) {
        string reg = "$s" + i;
        registers[reg] = 0;
    }
    for(int i = 0;i<=9;i++) {
        string reg = "$t" + i;
        registers[reg] = 0;
    }

    //parse input file
    string line;
    while(getline(in, line)) {
        instructions.push_back(parse_instruction(line));
    }

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

    if(operation.compare("add") == 0) {

    }
    else if(operation.compare("addi") == 0) {

    }
    else if(operation.compare("and") == 0) {

    }
    else if(operation.compare("andi") == 0) {

    }
    else if(operation.compare("or") == 0) {

    }
    else if(operation.compare("ori") == 0) {

    }
    else if(operation.compare("slt") == 0) {

    }
    else if(operation.compare("slti") == 0) {

    }
    else if(operation.compare("beq") == 0) {

    }
    else if(operation.compare("bne") == 0) {

    }
    else {

    }
}