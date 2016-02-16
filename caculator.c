#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define POOL_SIZE (1024)

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

struct __token__ token_pool[POOL_SIZE];
char *expression;

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
        printf("get [%c] \n", c);

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
                c = get_char();
                while(c >= '0' && c <= '9') {
                    c = get_char();
                    num[j++] = c;
                }
                token_pool[i].type    = TOKEN_INTEGER;
                token_pool[i++].value = atoi(num);
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

struct __token__ * get_token()
{
    static int i = 0;
    return &token_pool[i++];
}

int expect(int type)
{
    struct __token__ *ptoken = get_token();
    if (ptoken->type != type) {
        printf("%d expect %d\n", (ptoken-token_pool)/sizeof(struct __token__), type);
    }

}

#define error() do {printf("error: [%s][%d]\n", __func__, __LINE__); exit(-1);} while(0)

int factor()
{
    int s;
    struct __token__ *ptoken;
    ptoken = get_token();
    switch (ptoken->type) {
        case (TOKEN_INTEGER):
            s = ptoken->value;
            break;
        case (TOKEN_LPAREN):
            s = expr();
            expect(TOKEN_RPAREN);
            break;
        case (TOKEN_RPAREN):
            error();
            break;
        default:
            error();
            break;
    }

}

int term()
{
    int sum = 0;
    struct __token__ *ptoken;

    sum = term();

    while (1) {
        ptoken = get_token();
        switch (ptoken->type) {
            case (TOKEN_MUL):
                sum *= factor();
                break;
            case (TOKEN_DIV):
                sum /= factor();
                break;
            case (TOKEN_INVALD):
                error();
                break;
            defualt:
                error();
                break;
        }
    }

    return sum;
}

int expr(char *exp)
{
    int sum = 0;
    struct __token__ *ptoken;

    sum = term();

    while (1) {
        ptoken = get_token();
        switch (ptoken->type) {
            case (TOKEN_PLUS):
                sum += term();
                break;
            case (TOKEN_MINUS):
                sum -= term();
                break;
            case (TOKEN_INVALD):
                error();
                break;
            defualt:
                error();
                break;
        }
    }

    return sum;
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
        token_pool[i].type = TOKEN_INVALD;
    }

    printf("expr: %s\n", expression);
    parse_token();

    sum = expr(expression);
    printf("sum: %d\n", sum);
    return 0;
}
