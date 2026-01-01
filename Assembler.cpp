#include "Assembler.h"

unordered_map<string,int> opcodes;
vector<int> byte_code;
void opcode_type(){
    opcodes["PUSH"]=0x01;
    opcodes["POP"]=0x02;
    opcodes["DUP"]=0x03;
    opcodes["HALT"]=0xFF;
    opcodes["ADD"]=0x10;
    opcodes["SUB"]=0x11;
    opcodes["MUL"]=0x12;
    opcodes["DIV"]=0x13;
    opcodes["CMP"]=0x14;
    opcodes["JMP"]=0x20;
    opcodes["JZ"]=0x21;
    opcodes["JNZ"]=0x22;
    opcodes["STORE"]=0x30;
    opcodes["LOAD"]=0x31;
    opcodes["CALL"]=0x40;
    opcodes["RET"]=0x41;
   
  }
  vector<int> assemble(vector<string> program){
    for(int i=0;i<program.size();i++){
        string line=program[i];
         stringstream t(line);
         string opcod;
          t>>opcod;
          int values;
          byte_code.push_back(opcodes[opcod]);
          if(t>>values){
            byte_code.push_back(values);
          }

    }
  return byte_code;
}