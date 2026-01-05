
#include "Assembler.h"
#include <fstream>
#include<string>
#include<iostream>
using namespace std;
unordered_map<string,int> opcodes;
vector<int> byte_code;
unordered_map<string,int> label;
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
  /*vector<int> assemble(vector<string> program){
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
}*/

/*vector<int> assemble(const string& file){
  ifstream f1(file);
  string line;
  byte_code.clear();
    while(getline(f1,line)){
     if(line.empty()){
        continue;
     }
    
     stringstream t(line);
     string opcod;
      t>>opcod;
     byte_code.push_back(opcodes[opcod]);
   
    int value;
    if(t>>value){
      byte_code.push_back(value);
    }
      
    }
    return byte_code;
}*/
vector<int> assemble(const string& file){
  ifstream f1(file);
  string line;
  byte_code.clear();
  int pc=0;
  while(getline(f1,line)){
   
     int in=line.find(';');
    if(in!=string::npos){
      line=line.substr(0,in);
    }
     if(line.empty()){
      continue;
    }
    int index=line.find(':');
    if(index!=string::npos){//label exit
      string fin=line.substr(0,index);
      while(!fin.empty()&&isspace(fin.back()))
            fin.pop_back();
      //line.pop_back();
         label[fin]=pc;
    }
    else{
      string opcod;
      stringstream t(line);
      if(t>>opcod){
        pc++;
      }
      string value;
      if(t>>value){
        pc++;
      }
    }
  }
  f1.clear();f1.seekg(0,ios::beg);
  while(getline(f1,line)){
     
    int in=line.find(';');
    if(in!=string::npos){
      line=line.substr(0,in);
    }
    if(line.empty()){
      continue;
    }
     int index=line.find(':');
     if(index!=string::npos){
      continue;
     }

      string opcod;
      stringstream t(line);
      if( t>>opcod){
       byte_code.push_back(opcodes[opcod]);
      }
      string value;
      if( t>>value){
       if(label.find(value)!=label.end()){
          byte_code.push_back(label[value]);
        }
        else{
          cout<<"Value "<<value;
          byte_code.push_back(stoi(value));
        }
  }}
  for(auto &p:label){
    cout<<p.first<<" "<<p.second;
    
  }
  return byte_code;
}