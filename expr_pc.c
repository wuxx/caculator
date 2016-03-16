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
            printf("%d \n", op);
            error();
    }

    return sum;
}

struct __operator__ * get_op(int type)
{
    int i;
    for(i=0;i<(sizeof(operator)/sizeof(operator[0]));i++) {
        if (type == operator[i].type) {
            return &operator[i];
        }
    }

    assert(0);
    return NULL;
}

int is_op(int type)
{
    int i;
    for(i=0;i<(sizeof(operator)/sizeof(operator[0]));i++) {
        if (type == operator[i].type) {
            return 1;
        }
    }

    return 0;
}

int expr_left_operand()
{
    int sum = 0;

    if (ptoken->type == TOKEN_LPAREN) {

        ptoken = get_next_token();
        sum = __expr_pc(1);
        if (ptoken->type != TOKEN_RPAREN) {
            error();
        }
        ptoken = get_next_token();

    } else if (ptoken->type == TOKEN_INTEGER) {
        sum = ptoken->value;
        ptoken = get_next_token();
    } else {
        error();
    }

    return sum;
}

int __expr_pc(int min_prec)
{

    int op;
    int left,right;
    int prec, next_prec;
    int assoc;

    left = expr_left_operand();
    DEBUG("expr_left_operand return: %d \n", left);

    while (1) {

        if (ptoken->type == TOKEN_INVALD ||
            !is_op(ptoken->type)) {
            break;
        }

        op    = ptoken->type;
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

        right  = __expr_pc(next_prec);
        DEBUG("right: %d \n", right);

        left   = __expr__(op, left, right);
    }
    DEBUG("return %d \n", left);
    return left;
}

int expr_pc()
{
    PRINT_STAMP();
    ptoken = get_next_token();
    return __expr_pc(1);
}
