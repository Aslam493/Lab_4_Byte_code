
#include<iostream>
#include "VM.h"
#include "Assembler.h"
#include<vector>
using namespace std;
int main(){
  try{
  opcode_type();
 /*vector<string> programText = {
"PUSH 10",
"PUSH 3",
"SUB",
"HALT"

};


vector<int> program=assemble(programText);*/

vector<int> program=assemble("test1.asm");
cout<<"Byte_code"<<endl;
for(int i=0;i<program.size();i++){
    cout<<program[i]<<"  ";
}
cout<<endl;
Virtual vm(program.data(),program.size());
vm.run();
 vm.printStack();
 vm.printMemory();
   cout<<"program finished";
}
catch (const exception& error){
  cout<<"Error "<<error.what()<<endl;
}
}