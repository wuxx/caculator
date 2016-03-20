/* stupid loop --- I write this algorithm */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>

#include "caculator.h"

extern struct __token__ token_pool[POOL_SIZE];

int token_num(int start, int end)
{
    int i, num = 0;
    
    for(i=0;i<end;i++) {
        if (token_pool[i].type != TOKEN_INVALD) {
            num ++ ;
        }
    }
}

int __expr_sl(int start, int end)
{
    int i;
    while(token_num(start, end) != 1) {
    }

    for(i=0;i<end;i++) {
        if (token_pool[i].type == TOKEN_INTEGER) {
            return token_pool[i].value;
        }
    }

}

int expr_sl()
{
    int i, len = 0;
    /* get the size */
    for(i=0;i<POOL_SIZE;i++) {
        if(token_pool[i].type == TOKEN_INVALD) {
            len = i;
        }
    }
    return __expr_sl(0, len);
}
