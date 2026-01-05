#ifndef ASSEMBLER_H
#define ASSEMBLER_H
#include<string>
#include<vector>
#include<sstream>
#include <unordered_map>

using namespace std;
extern unordered_map<string ,int> opcodes;
extern vector<int> byte_code;
//vector<int> assemble(vector<string> program);
vector<int> assemble(const string& file);
void opcode_type();
#endif
