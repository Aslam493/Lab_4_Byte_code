#ifndef VM_H
#define VM_H
#include<iostream>
#include<stdexcept>
using namespace std;
class Virtual{
 public:
    
     static const int stack_capacity=256;
      int stack[stack_capacity];
     int sp=-1;
     bool running=true;
     int program[256];
     int Memory[256];
     int return_stack[256];
     int rsp=-1;
     int pc=0;
     int size_program=0;
     Virtual(const int code[],int size){
        for(int i=0;i<size;i++){
            program[i]=code[i];
        }
        size_program=size;
       
     }
   void push(int v){
    if(sp>=stack_capacity){
      cout<<"Overflow occcur<<endl";
      return;
    }
    stack[++sp]=v;
   }
   int pop(){
    if(sp<0){
        cout<<"Underflow error";
        return -1;
    }
   return stack[sp--];
   }
   int peek(){
    if(sp==-1){
        cout<<"stack is empty";
         return -1;
    }
    return stack[sp];
   }
   void return_push(int v){
    if(rsp>=stack_capacity){
        cout<<"Overflow occur";
        return;
    }
    return_stack[++rsp]=v;
   }
    int return_pop(){
    if(rsp<0){
        cout<<"Underflow error";
        return -1;
    }
   return return_stack[rsp--];
   }
   int return_peek(){
    if(rsp==-1){
        cout<<"stack is empty";
         return -1;
    }
    return return_stack[rsp];
   }

   void run(){
      while(running&&pc<size_program){
        int opcode=program[pc];
        cout<<"OPcode "<<opcode;
        cout<<endl;
        switch(opcode)
        {
            case 0x01:
             {
                int v=program[++pc];
                push(v);
                cout<<"push "<<v;
                break;
             }
             case 0x02:
             {
                int v=pop();
                 cout<<"pop "<<v;
                break;
             }
             case 0x03:
             {
                int v=peek();
                push(v);

                break;
             }
             case 0x10:
             {
                int a=pop();
                int b=pop();
                push(b+a);
                break;
             }
             case 0x11:
             {
                int a=pop();
                int b=pop();
                push(b-a);
                break;
             }
             case 0x12:{
               int a=pop();
               int b=pop();
               push(b*a);
               break;
             }
             case 0x13:
             {
                int a=pop();
                int b=pop();
                push(b/a);
                break;
             }
             case 0x14:
             {
                int a=pop();
                int b=pop();
                if(a<b){
                    push(1);
                }
                else{
                    push(0);
                }
                break;
             }
             case 0x20:{
                int address=program[++pc];
                pc=address-1;
                break;
             }
             case 0x21:
             {
                int t=pop();
                if(t==0){
                    int address=program[++pc];
                    pc=address-1;
                   
                }
                break;
             }
             case 0x22:
             {
                int t=pop();
                if(t!=0){
                    int address=program[++pc];
                    pc=address-1;

                }
                break;
             }
             case 0x30:
             {
                int adress=program[++pc];
                int t=pop();
                Memory[adress]=t;
                break;
             }
             case 0x31:
             {
                int address=program[++pc];
                push(Memory[address]);
                break;
             }
             case 0x40:
             {
                int address=program[++pc];
                return_push(pc+1);
                pc=address-1;
                break;
             }
             case 0x41:
             {
                pc=return_pop()-1;
                break;
             }
             case 0xFF:
             {
                running =false;
                break;
             }
              default:
             {
                cout<<"Error\n";
                break;
             }
        }
        pc++;
         
      }
   }
   void printStack() {
    cout << "\nSTACK: ";
    for (int i = 0; i <= sp; i++) {
        cout << stack[i] << " ";
    }
    cout << endl;
}
   void printMemory(){
     cout<<Memory[0];
   }
};
#endif