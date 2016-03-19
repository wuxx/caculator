/* shunting yard */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>

#include "caculator.h"

extern int __expr__(int op, int l, int r);

#define STACK_SIZE (1024)

int op_stack[STACK_SIZE];
int sp = STACK_SIZE - 1;

extern struct __token__ * get_next_token();

struct __token__ * ptoken;

static int sindex = 0;
struct __token__ sy_token_pool[POOL_SIZE];

void __push(int x)
{
    sp -- ;
    op_stack[sp] = x;
    assert(sp >= 0);
}

int __pop()
{
    int x;
    if (sp == STACK_SIZE) {
        return -1;
    } else {
        x = op_stack[sp];
        sp ++;
        return x;
    }
}

int prio(int type)
{
    switch (type) {
        case (TOKEN_PLUS):
            return 1;
        case (TOKEN_MINUS):
            return 1;
        case (TOKEN_MUL):
            return 2;
        case (TOKEN_DIV):
            return 2;
        case (TOKEN_LPAREN):
            return 100;
        case (TOKEN_RPAREN):
            return 100;
        default:
            error();
    }
}

int __expr_sy()
{
    int type;
    while (ptoken->type != TOKEN_INVALD) {
        switch(ptoken->type) {
            case (TOKEN_INTEGER):
                memcpy(&sy_token_pool[sindex], ptoken, sizeof(struct __token__));
                sindex++;
                break;
            case (TOKEN_PLUS):
            case (TOKEN_MINUS):
            case (TOKEN_MUL):
            case (TOKEN_DIV):
                type = __pop();
                if (type >= ptoken->type) {
                    while (type >= ptoken->type) {
                        sy_token_pool[sindex].type = type;
                        type = __pop();
                        sindex++;
                    }

                __push(type);
                } else {
                    __push(type);
                    __push(ptoken->type);
                }
                break;
            case (TOKEN_LPAREN):
                __push(ptoken->type);
                break;
            case (TOKEN_RPAREN):
                type = __pop();
                while (type != TOKEN_LPAREN) {
                        sy_token_pool[sindex].type = type;
                        sindex++;
                        type = __pop();
                }
                break;

        }
    }
    type = __pop();
    while (type != -1) {
        sy_token_pool[sindex].type = type;
        sindex++;
    }
}

int expr_sy()
{
    PRINT_STAMP();
    ptoken = get_next_token();
    return __expr_sy();
}
