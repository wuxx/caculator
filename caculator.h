#ifndef __CACULATOR_H__
#define __CACULATOR_H__

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define POOL_SIZE (1024)

#if 1
#define DEBUG(fmt, ...)     printf("[%s][%d]" fmt,  __func__, __LINE__, ##__VA_ARGS__)
#else
#define DEBUG(fmt, ...)
#endif

#define PRINT_STAMP() DEBUG("\n")
#define error() do {printf("error: [%s][%d]\n", __func__, __LINE__); exit(-1);} while(0)

enum TOKEN_E {
    TOKEN_INVALD = 0,
    TOKEN_INTEGER,
    TOKEN_PLUS,
    TOKEN_MINUS,
    TOKEN_MUL,
    TOKEN_DIV,
    TOKEN_LPAREN,
    TOKEN_RPAREN,
    TOKEN_MAX,
};

struct __token__ {
    int type;
    int value;
};

extern int expr_pc();

#endif /* __CACULATOR_H__ */
