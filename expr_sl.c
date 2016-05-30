/* stupid loop --- I write this algorithm */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>

#include "caculator.h"

extern struct __token__ token_pool[POOL_SIZE];

static int __expr__(int index, int end)
{
    int i, j;
    int x, y, sum;
    DEBUG("%d %d \n", index, end);
    for(i=index-1;i>=0;i--) {
        if (token_pool[i].type != TOKEN_INVALID) {
            assert(token_pool[i].type == TOKEN_INTEGER);
            x = token_pool[i].value;
            break;
        }
    }

    for(j=index+1;j<end;j++) {
        if (token_pool[j].type != TOKEN_INVALID) {
            assert(token_pool[j].type == TOKEN_INTEGER);
            y = token_pool[j].value;
            break;
        }
    }
    DEBUG("type: %d; x: %d; y: %d \n", token_pool[index].type, x, y);
    switch (token_pool[index].type) {
        case (TOKEN_PLUS):
            sum = x + y;
            break;
        case (TOKEN_MINUS):
            sum = x - y;
            break;
        case (TOKEN_MUL):
            sum = x * y;
            break;
        case (TOKEN_DIV):
            sum = x / y;
            break;
    }

    token_pool[index].type  = TOKEN_INTEGER;
    token_pool[index].value = sum;

    token_pool[i    ].type = TOKEN_INVALID;
    token_pool[j    ].type = TOKEN_INVALID;

    DEBUG("return %d \n", sum);
    return sum;

}

int get_highest_op(int start, int end)
{
    int i, j = -1;
    DEBUG("%d %d \n", start, end);
    for(i=start;i<end;i++) {
        if(token_pool[i].type == TOKEN_PLUS  ||
           token_pool[i].type == TOKEN_MINUS ||
           token_pool[i].type == TOKEN_MUL   ||
           token_pool[i].type == TOKEN_DIV ) {

            if (j == -1) j = i;

            if (token_pool[i].type > token_pool[j].type) {
                j = i;
            }
        }
    }

    return j;
}

int __expr_sl(int start, int end)
{
    int i;
    while(1) {
        i = get_highest_op(start, end);
        if ( i != -1) {
            DEBUG("i %d \n", i);
            __expr__(i, end);
        } else {
            break;
        }
    }
    /* done */
    
    for(i=0;i<end;i++) {
        if (token_pool[i].type == TOKEN_INTEGER) {
            break;
        }
    }

    return token_pool[i].value;

}

int expr_sl()
{
    int i, len = 0;
    /* get the size */
    for(i=0;i<POOL_SIZE;i++) {
        if(token_pool[i].type == TOKEN_INVALID) {
            len = i;
            break;
        }
    }
    return __expr_sl(0, len);
}
