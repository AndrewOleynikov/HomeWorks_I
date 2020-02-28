#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#include "hashtable.h"
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


size_t codeToNumb(char *str)
{
    if (strstr(str, ";"))
    {
        return NO_COMAND;
    }
    if (strstr(str, "ld") && !strstr(str, "ldc"))
    {
        return ld;
    }
    if (strstr(str, "st"))
    {
        return st;
    }
    if (strstr(str, "ldc"))
    {
        return ldc;
    }
    if (strstr(str, "add"))
    {
        return add;
    }
    if (strstr(str, "sub"))
    {
        return sub;
    }
    if (strstr(str, "cmp"))
    {
        return cmp;
    }
    if (strstr(str, "jmp"))
    {
        return jmp;
    }
    if (strstr(str, "br"))
    {
        return br;
    }
    if (strstr(str, "ret"))
    {
        return ret;
    }
    return NO_COMAND;
}

size_t HashH37( char * word )
{
    size_t hash = 2139062143;
    for(; *word; word++)
    {
        hash = 37 * hash + *word;
    }
    return hash;
}

void parsingLabels(struct Interpreter *inter, FILE *progFile)
{
    size_t numOfStr = 0;
    char buf[20] = {0};
    while (fgets(buf, sizeof(buf)/sizeof(char), progFile))
    {
        if (codeToNumb(buf) == NO_COMAND)
        {
            continue;
        }
        size_t dumb = 0;
        while (strchr(buf, ':'))
        {
            size_t colonIt = strcspn(buf, ":");
            char lableName[colonIt - dumb];
            size_t dumbInto = 0;

            for (size_t i = dumb; i < colonIt; i++)
            {
                if (buf[i] == ' ')
                {
                    dumbInto++;
                    continue;
                }
                lableName[i - dumb] = buf[i];
                buf[i] = ' ';
                dumbInto++;
            }
            lableName[colonIt - dumb] = 0;
            buf[colonIt] = ' ';
            dumb += dumbInto + 2;

            addToTable(inter->program.lablesMas, lableName, numOfStr);

            for (size_t i = 0; i < colonIt; i++)
            {
                lableName[i] = 0;
            }
        }
        numOfStr++;
        for (size_t i = 0; i < sizeof(buf)/sizeof(char); i++)
        {
            buf[i] = 0;
        }
    }
    inter->program.sizeOfProgram = numOfStr;
}

char* withoutLables( char *str)
{
    size_t N = strlen(str);
    char *help = (char*)malloc((sizeof(char)) * N);
    for (int32_t i = N - 1; i >= 0; i--)
    {
        help[i] = str[N - 1 - i];
    }
    size_t colonIt = strcspn(help, ":");
    help[colonIt] = 0;
    size_t i, j;
    i = 0;
    j = colonIt - 2;
    while (j > i)
    {
        help[i] = help[i] ^ help[j];
        help[j] = help[i] ^ help[j];
        help[i] = help[j] ^ help[i];
        i++;
        j--;
    }
    help[colonIt] = 0;
    return help;
}

char *strFormFile(char *str)
{
    size_t pt = 0;
    while (str[pt] != '\n')
    {
        pt++;
    }
    str[pt] = 0;
    return str;
}

int32_t helperStrToInt(char *str)
{
    size_t N = strlen(str);
    int32_t res = 0;
    for (size_t i = 0; i < N; i++)
    {
        res = res * 10 + (int32_t)(str[i] - '0');
    }
   return res;
}

int32_t strToInt(char *str)
{
    if(*str == '-')
    {
        return (-1) * helperStrToInt(str + 1);
    }
    return helperStrToInt(str);
}

void createByteCode(struct Interpreter *inter, FILE *progFile)
{
    char buf[BUF_SIZE] = {0};
    size_t i = 0;
    while (fgets(buf, sizeof(buf)/sizeof(char), progFile))
    {
        if (codeToNumb(buf) == NO_COMAND)
        {
            continue;
        }
        if (strstr(buf, "ld") && !strstr(buf, "ldc"))
        {
            char *argCh = strFormFile(strstr(buf, "ld")) + 3;
            int32_t argInt = strToInt(argCh);
            inter->program.comands[i].arg = argInt;
            inter->program.comands[i].opCode = ld;
        }
        if (strstr(buf, "st"))
        {
            char *argCh = strFormFile(strstr(buf, "st")) + 3;
            int32_t argInt = strToInt(argCh);
            inter->program.comands[i].arg = argInt;
            inter->program.comands[i].opCode = st;
        }
        if (strstr(buf, "ldc"))
        {
            char *argCh = strFormFile(strstr(buf, "ldc")) + 4;
            int32_t argInt = strToInt(argCh);
            inter->program.comands[i].arg = argInt;
            inter->program.comands[i].opCode = ldc;
        }
        if (strstr(buf, "jmp"))
        {
            char *argCh = strFormFile(strstr(buf, "jmp")) + 4;
            int32_t argInt = strToInt(argCh);
            inter->program.comands[i].arg = find(inter->program.lablesMas, argCh);
            inter->program.comands[i].opCode = jmp;
        }
        if (strstr(buf, "br"))
        {
            char *argCh = strFormFile(strstr(buf, "br")) + 3;
            int32_t argInt = strToInt(argCh);
            inter->program.comands[i].arg = find(inter->program.lablesMas, argCh);
            inter->program.comands[i].opCode = br;
        }
        if (strstr(buf, "add"))
        {
            inter->program.comands[i].opCode = add;
        }
        if (strstr(buf, "sub"))
        {
            inter->program.comands[i].opCode = sub;
        }
        if (strstr(buf, "cmp"))
        {
            inter->program.comands[i].opCode = cmp;
        }
        if (strstr(buf, "ret"))
        {
            inter->program.comands[i].opCode = ret ;
        }
        i++;
    }
    return inter;
}

void printBC(struct Interpreter inter)
{
    for (size_t i = 0; i < inter.program.sizeOfProgram; i++)
    {
           printf("%d : %d ~~ %d\n",i, inter.program.comands[i].opCode, inter.program.comands[i].arg);
    }
}

void pushStack(struct Stack *stack, int32_t value)
{

    if (stack->size >= 1024)
    {
        printf("ERRORst");
        return;
    }
    stack->data[stack->size] = value;
    stack->size++;
}

int32_t headValue(struct Stack *stack)
{
    return stack->data[stack->size - 1];
}

void loadToStack(struct Stack *stack, int32_t *mem, int32_t it)
{
    pushStack(stack, mem[it]);
}

void loadToMem(struct Stack *stack, int32_t *mem, int32_t arg)
{
    mem[arg] = headValue(stack);
    stack->size--;
}

void addStack(struct Stack *stack)
{
    stack->data[stack->size] = stack->data[stack->size - 1] + stack->data[stack->size - 2];
    stack->size++;
}

void subStack(struct Stack *stack)
{
    stack->data[stack->size] = stack->data[stack->size - 1] - stack->data[stack->size - 2];
    stack->size++;
}

void cmpStack(struct Stack *stack)
{
    if (stack->data[stack->size - 1] > stack->data[stack->size - 2])
    {
        stack->data[stack->size] = 1;
        stack->size++;
        return;
    }
    if (stack->data[stack->size - 1] < stack->data[stack->size-2])
    {
        stack->data[stack->size] = -1;
        stack->size++;
        return;
    }
    stack->data[stack->size] = 0;
    stack->size++;
}

void jumpTo(int32_t *ip, int32_t lable)
{
    *ip = lable - 1;
}

void brTo(int32_t *ip, struct Stack *stack, int32_t lable)
{
    if (headValue(stack) != 0)
    {
        *ip = lable - 1;
    }
    return;
}

void printS(struct Interpreter inter)
{
    if(inter.state.stack.size)
    printf("TOP %d\n", headValue(&inter.state.stack));
    else printf("STACKEMPT\n");
    printf("MEM:\n");
    for(int32_t i = 0; i < MEMORY_MAX; i++)
    {
        printf("   %d~%d\n", i, inter.state.memory[i]);
    }
    printf("-------------------------------\n");
}

void execuite(struct Interpreter *inter)
{
    int32_t i = 0;
    struct Stack *stack = &(inter->state.stack);
    while (1)
    {
        int32_t arg = inter->program.comands[i].arg;
        switch (inter->program.comands[i].opCode)
        {
            case ld:
                loadToStack(stack, inter->state.memory, arg);
                break;
            case st:
                loadToMem(stack, inter->state.memory, arg);
                break;
            case ldc:
                pushStack(stack, arg);
                break;
            case add:
                addStack(stack);
                break;
            case sub:
                subStack(stack);
                break;
            case cmp:
                cmpStack(stack);
                break;
            case jmp:
                jumpTo(&i, arg);
                break;
            case br:
                brTo(&i, stack, arg);
                break;
            case ret:
                printf("RET %d\n", headValue(stack));
                return;
                break;
            default:
                printf("SMTH_WRONG");
        }
        i++;
    }
}

void startInterpretr(struct Interpreter *inter)
{
    inter->program.comands = (struct Comand*)malloc(sizeof(struct Comand) * COUNT_OF_CMD);
    inter->state.stack.size = 0;
    inter->program.lablesMas = createHashTable(COUNT_OF_CMD, HashH37);
    inter->state.memory = (int32_t*)malloc(sizeof(int32_t) * MEMORY_MAX);
}

void endInterpretr(struct Interpreter *inter)
{
    free(inter->program.comands);
    free(inter->state.memory);
    deleteHashTable(inter->program.lablesMas);
}

int32_t main()
{
    struct Interpreter inter;
    startInterpretr(&inter);

    FILE *progFile = fopen("program.txt", "r");
    if (!progFile)
    {
        printf("ERROR");
        exit(1);
    }
    parsingLabels(&inter, progFile);
    fclose(progFile);

    progFile = fopen("program.txt", "r");
    if (!progFile)
    {
        printf("ERROR");
        exit(1);
    }
    createByteCode(&inter, progFile);
    fclose(progFile);

    execuite(&inter);
    endInterpretr(&inter);

    return 0;
}
