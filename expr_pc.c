/* precedence climbing */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <stdarg.h>

#include "caculator.h"

int __expr_pc(int min_prec);

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

int level = 0;
void level_printf(const char *format, ...)
{
    int i;
    va_list args;
    static char log_buf[1024];

    for(i=0;i<level;i++) {
        printf("\t");
    }

    va_start(args,format);
    vsnprintf(log_buf,sizeof(log_buf), format, args);
    va_end(args);
    printf("%s", log_buf);
}

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

    error();
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

    level ++ ;
    left = expr_left_operand();
    level_printf("left: %d \n", left);

    while (1) {

        level_printf("__enter__ while\n");

        if (ptoken->type == TOKEN_INVALID ||
            !is_op(ptoken->type)) {
            level_printf("__exit1__ while\n");
            break;
        }

        op    = ptoken->type;
        pop   = get_op(ptoken->type);
        prec  = pop->prec;
        assoc = pop->as;

        if (prec < min_prec) {
            level_printf("__exit2__ while\n");
            break;
        }

        if (assoc == LEFT) {
            next_prec = prec + 1;
        } else {
            next_prec = prec;
        }

        ptoken = get_next_token();

        right  = __expr_pc(next_prec);
        level_printf("right: %d \n", right);

        level_printf("update left: (%d, %d)", left, right);

        left   = __expr__(op, left, right);

        printf("-> %d \n", left);
    }

    level_printf("return %d \n", left);
    level -- ;
    return left;
}

int expr_pc()
{
    ptoken = get_next_token();
    return __expr_pc(1);
}
