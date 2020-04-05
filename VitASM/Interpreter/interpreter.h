#ifndef INTERPRETER_H_INCLUDED
#define INTERPRETER_H_INCLUDED

#include <stdint.h>

#define STACK_MAX 1024
#define MEMORY_MAX 1024 * 1024
#define COUNT_OF_CMD 200
#define BUF_SIZE 20
#define NO_COMAND 99

struct Stack
{
    int32_t data[STACK_MAX];
    int32_t size;
};

struct State
{
    struct Stack stack;
    int32_t *memory;
};

struct Comand
{
    int32_t opCode;
    int32_t arg;
};

struct Program
{
    struct Comand *comands;
    struct HashTable *lablesMas;
    size_t sizeOfProgram;
};

struct Interpreter
{
    struct Program program;
    struct State state;
};

enum OpCodes
{
    ld ,
    st ,
    ldc,
    add,
    sub,
    cmp,
    jmp,
    br ,
    ret
};
size_t codeToNumb(char *str);
size_t HashH37(char * word);
void parsingLabels(struct Interpreter *inter, FILE *progFile);
char *strFormFile(char *str);
int32_t helperStrToInt(char *str);
int32_t strToInt(char *str);
void createByteCode(struct Interpreter *inter, FILE *progFile);
void printBC(struct Interpreter inter);
void pushStack(struct Stack *stack, int32_t value);
int32_t headValue(struct Stack *stack);
void loadToStack(struct Stack *stack, int32_t *mem, int32_t it);
void loadToMem(struct Stack *stack, int32_t *mem, int32_t arg);
void addStack(struct Stack *stack);
void subStack(struct Stack *stack);
void cmpStack(struct Stack *stack);
void jumpTo(int32_t *ip, int32_t lable);
void brTo(int32_t *ip, struct Stack *stack, int32_t lable);
void printS(struct Interpreter inter);
void execuite(struct Interpreter *inter);
void startInterpretr(struct Interpreter *inter);
void endInterpretr(struct Interpreter *inter);

#endif // INTERPRETER_H_INCLUDED
