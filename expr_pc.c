#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>

#include "caculator.h"

extern struct __token__ * get_next_token();

enum ASSOC_E {
    LEFT = 0,
    RIGHT,
};

struct __operator__ {
    int type;
    int prec;   /* 0: lowest; 100: highest */
    int  as;    /* LEFT or RIGHT */
};

struct __operator__ operator[] = {
    {TOKEN_PLUS,  1, LEFT},
    {TOKEN_MINUS, 1, LEFT},
    {TOKEN_MUL,   2, LEFT},
    {TOKEN_DIV,   2, LEFT},
};

/* point to current token */
struct __token__    * ptoken;
struct __operator__ * pop;

int __expr__(int op, int l, int r)
{
    int sum = 0;
    switch(op) {
        case (TOKEN_PLUS):
            sum = l + r;
            break;
        case (TOKEN_MINUS):
            sum = l - r;
            break;
        case (TOKEN_MUL):
            sum = l * r;
            break;
        case (TOKEN_DIV):
            sum = l / r;
            break;
        default:
            error();
    }

    return sum;
}

struct __operator__ * get_op(int type)
{
    int i;
    for(i=0;i<(sizeof(operator)/sizeof(operator));i++) {
        if (type == operator[i].type) {
            return &operator[i];
        }
    }

    assert(0);
    return NULL;
}

int expr_left_operand()
{
    int ret = 0;

    if (ptoken->type == TOKEN_LPAREN) {

        ptoken = get_next_token();
        ret = __expr_pc(1);
        ptoken = get_next_token();
        if (ptoken->type != TOKEN_LPAREN) {
            error();
        }

    } else if (ptoken->type == TOKEN_INTEGER) {
        ret = ptoken->value;
        ptoken = get_next_token();
    }

    return ret;
}

int __expr_pc(int min_prec)
{

    int op;
    int left,right;
    int prec, next_prec;
    int assoc;

    left = expr_left_operand();

    while (1) {

        pop   = get_op(ptoken->type);
        prec  = pop->prec;
        assoc = pop->as;

        if (prec < min_prec) {
            break;
        }

        if (assoc == LEFT) {
            next_prec = prec + 1;
        } else {
            next_prec = prec;
        }
        

        ptoken = get_next_token();

        right = __expr_pc(next_prec);

        left  = __expr__(op, left, right);
    }
}

int expr_pc()
{

    ptoken = get_next_token();
    return __expr_pc(1);
}
