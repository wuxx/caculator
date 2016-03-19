/* stupid loop --- I write this algorithm */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>

#include "caculator.h"

extern struct __token__ token_pool[POOL_SIZE];

int __expr_sl(int start, int end)
{

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
