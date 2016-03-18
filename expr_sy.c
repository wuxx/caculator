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

struct __token__    * ptoken;

void __push(int x)
{
    op_stack[sp] = x;
    sp -- ;
    assert(sp >= 0);
}

int __pop()
{
    sp ++ ;
    assert(sp < STACK_SIZE);
    return op_stack[sp];
}

int __expr_sy()
{

}

int expr_sy()
{
    PRINT_STAMP();
    ptoken = get_next_token();
    return __expr_sy();
}
