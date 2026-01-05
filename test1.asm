PUSH 2
STORE 0        ; outer = 2

outer:
PUSH 3
STORE 1        ; inner = 3

inner:
LOAD 1
PUSH 1
SUB
STORE 1
JNZ inner

LOAD 0
PUSH 1
SUB
STORE 0
JNZ outer

HALT
