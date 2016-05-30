#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "caculator.h"

extern int expr_dc();
extern int expr_pc();
extern int expr_sy();
extern int expr_sl();

char * token_desc[] = {
    "TOKEN_INVALID",
    "TOKEN_INTEGER",
    "TOKEN_PLUS",
    "TOKEN_MINUS",
    "TOKEN_MUL",
    "TOKEN_DIV",
    "TOKEN_LPAREN",
    "TOKEN_RPAREN",
    "TOKEN_MAX",
};

struct __token__ token_pool[POOL_SIZE];
char *expression;
int tk_index = 0;

char get_char()
{
    static int i = 0;
    return expression[i++];
}

int parse_token()
{
    char c;
    int i = 0, j;
    char num[11];
    c = get_char();
    while(1) {
        DEBUG("get [%c] \n", c);

        switch (c) {
            case ('+'):
                token_pool[i++].type = TOKEN_PLUS;
                c = get_char();
                break;
            case ('-'):
                token_pool[i++].type = TOKEN_MINUS;
                c = get_char();
                break;
            case ('*'):
                token_pool[i++].type = TOKEN_MUL;
                c = get_char();
                break;
            case ('/'):
                token_pool[i++].type = TOKEN_DIV;
                c = get_char();
                break;
            case ('('):
                token_pool[i++].type = TOKEN_LPAREN;
                c = get_char();
                break;
            case (')'):
                token_pool[i++].type = TOKEN_RPAREN;
                c = get_char();
                break;
            case ('0'): case ('1'): case ('2'): case ('3'): case ('4'):
            case ('5'): case ('6'): case ('7'): case ('8'): case ('9'):
                memset(num, 0, sizeof(num));
                j = 0;
                num[j++] = c;
                while(c >= '0' && c <= '9') {
                    c = get_char();
                    num[j++] = c;
                }
                token_pool[i].type    = TOKEN_INTEGER;
                token_pool[i++].value = atoi(num);
                DEBUG("[%s] %d \n", num, token_pool[i-1].value);
                /**/
                break;
            case ('\0'):
                return 0;
                break;
            default:
                printf("unrecognized char [%c]\n", c);
                exit(-1);
                break;
        }
    }
}

struct __token__ * get_next_token()
{
    DEBUG("get %s [%d] \n", token_desc[token_pool[tk_index].type], token_pool[tk_index].value);
    return &token_pool[tk_index++];
}

int put_token()
{
    DEBUG(" tk_index: %d \n", tk_index);
    tk_index -- ;
    return 0;
}

int expect(int type)
{
    struct __token__ *ptoken = get_next_token();
    if (ptoken->type != type) {
        printf("%d expect %d\n", (ptoken-token_pool)/sizeof(struct __token__), type);
    }
    return 0;
}

int expr()
{
    /* decline recursive analysis */
    return expr_dc();

    /* precedence climbing */
    /* return expr_pc(); */

    /* shunting yard */
    /* return expr_sy(); */

    /* stupid loop */
    /* return expr_sl(); */
}

int main(int argc, char **argv)
{
    int i, sum;

    if (argc != 2) {
        printf("%s \"expression\"\n", argv[0]);
        return -1;
    }

    /* init */
    expression = argv[1];
    for(i=0;i<sizeof(token_pool)/sizeof(token_pool[0]);i++) {
        token_pool[i].type = TOKEN_INVALID;
    }

    DEBUG("expr: %s\n", expression);
    parse_token();

    sum = expr();
    printf("sum: %d\n", sum);
    return 0;
}
