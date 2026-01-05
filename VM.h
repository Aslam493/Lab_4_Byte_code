

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
        for (int i = 0; i < 256; i++) Memory[i] = 0;

        size_program=size;
       
     }
   void push(int v){
    if(sp>=stack_capacity-1){
     throw runtime_error("Overflow");
      
    }
    stack[++sp]=v;
   }
   int pop(){
    if(sp<0){
        throw runtime_error("Underflow");
    }
   return stack[sp--];
   }
   int peek(){
    if(sp==-1){
         throw runtime_error("Stack is empty");
    }
    return stack[sp];
   }
   void return_push(int v){
    if(rsp>=stack_capacity-1){
        throw runtime_error("Overflow");
    }
    return_stack[++rsp]=v;
   }
    int return_pop(){
    if(rsp<0){
         throw runtime_error("Underflow");
    }
   return return_stack[rsp--];
   }
   int return_peek(){
    if(rsp==-1){
        throw runtime_error("Stack is empty");
    }
    return return_stack[rsp];
   }

   void run(){
      try{
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
                cout<<"push "<<v<<endl;
                break;
             }
             case 0x02:
             {
                int v=pop();
                 cout<<"pop "<<v<<endl;
                break;
             }
             case 0x03:
             {
                int v=peek();
                push(v);
                cout<<"peek "<<v<<endl;
                break;
             }
             case 0x10:
             {
                int a=pop();
                int b=pop();
                push(b+a);
                 cout<<"Add "<<b+a<<endl;
                break;
             }
             case 0x11:
             {
                int a=pop();
                int b=pop();
                push(b-a);
                 cout<<"sub "<<b-a<<endl;
                break;
             }
             case 0x12:{
               int a=pop();
               int b=pop();
               push(b*a);
                cout<<"mul "<<b*a<<endl;
               break;
             }
             case 0x13:
             {
                int a=pop();
                int b=pop();
                if(a==0){
                  throw runtime_error("Division by zero");
                }
                push(b/a);
                 cout<<"div "<<b/a<<endl;
                break;
             }
             case 0x14:
             {
                int b=pop();
                int a=pop();
                if(a<b){
                   cout<<"if "<<1<<endl;
                    push(1);
                }
                else{
                   cout<<"else "<<0<<endl;
                    push(0);
                }
                break;
             }
             case 0x20:{
                int address=program[++pc];
                if(address<0||address>=256){
                  throw runtime_error("Invalid address to access "+to_string(address));
                }
                pc=address-1;

                break;
             }
             case 0x21:
             {
                
               // cout<<"pc "<<pc<<endl;
                int address=program[++pc];
                   if(address<0||address>=256){
                  throw runtime_error("Invalid address to access "+to_string(address));
                }
                int t=pop();
                if(t==0){
                    
                    pc=address-1;
                   
                }
               // cout<<"t "<<t<<endl;
                //cout<<"adress "<<address;
                //cout<<"pc "<<pc<<endl;
                break;
             }
             case 0x22:
             {
             
                 int address=program[++pc];
                 if(address<0||address>=256){
                  throw runtime_error("Invalid address to access "+to_string(address));
                }
                  cout<<"sp "<<sp;
                  
                   cout<<endl;
                   int t=pop();
                if(t!=0){
                   
                    pc=address-1;

                }
                break;
             }
             case 0x30:
             {
                    int t=pop();
                int adress=program[++pc];
                if(adress<0||adress>=256){
                   throw runtime_error("Memeory acess not Performed Properly"+to_string(adress));
                }
            
                Memory[adress]=t;
                break;
             }
             case 0x31:
             {
                int address=program[++pc];
                if(address<0||address>=256){
                  throw runtime_error("Invalid address to access "+to_string(address));
                }
                push(Memory[address]);
                break;
             }
             case 0x40:
             {
                int address=program[++pc];
                if(address<0||address>=256){
                  throw runtime_error("Invalid address to access "+to_string(address));
                }
                return_push(pc+1);
                pc=address-1;
                break;
             }
             case 0x41:
             {  
                if(rsp<0){
                  throw runtime_error("Return stack is Empty");
                }
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
    catch(const runtime_error& error){
      cout<<"Error in Run "<<error.what()<<endl;
      running=false;
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
     for (int i = 0; i < 256; i++) 
     {
     
      if(Memory[i] != 0){
         cout<<"Data at Memory Location "<<Memory[i];
      }
     }

   }
};
#endif