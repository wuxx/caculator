#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define POOL_SIZE (1024)
#define PRINT_STAMP() printf("[%s][%d]\n", __func__, __LINE__)

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

char *token_desc[] = {
    "TOKEN_INVALD",
    "TOKEN_INTEGER",
    "TOKEN_PLUS",
    "TOKEN_MINUS",
    "TOKEN_MUL",
    "TOKEN_DIV",
    "TOKEN_LPAREN",
    "TOKEN_RPAREN",
    "TOKEN_MAX",
};

struct __token__ {
    int type;
    int value;
};

struct __token__ token_pool[POOL_SIZE];
char *expression;
int token_index = 0;
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
                while(c >= '0' && c <= '9') {
                    c = get_char();
                    num[j++] = c;
                }
                token_pool[i].type    = TOKEN_INTEGER;
                token_pool[i++].value = atoi(num);
                printf("11111111111111 %s [%s] %d \n", __func__, num, token_pool[i-1].value);
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
    printf("in %s get %s %d\n", __func__, token_desc[token_pool[token_index].type], token_pool[token_index].value);
    return &token_pool[token_index++];
}

int put_token()
{
    printf("in %s \n", __func__);
    token_index -- ;
    return 0;
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
    int sum;
    struct __token__ *ptoken;
    ptoken = get_token();
    switch (ptoken->type) {
        case (TOKEN_INTEGER):
            PRINT_STAMP();
            sum = ptoken->value;
            printf("in1 %s sum : %d\n", __func__, sum);
            PRINT_STAMP();
            return sum;
            break;
        case (TOKEN_LPAREN):
            sum = expr();
            printf("in2 %s sum : %d\n", __func__, sum);
            expect(TOKEN_RPAREN);
            return sum;
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

    PRINT_STAMP();
    sum = factor();
    printf("in %s sum: %d\n", __func__, sum);
    PRINT_STAMP();


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
                return sum;
                break;
            default:
                put_token();
                return sum;
                break;
        }
    }

    return sum;
}

int expr(char *exp)
{
    int sum = 0;
    struct __token__ *ptoken;
    PRINT_STAMP();
    sum = term();
    printf("sum: %d\n", sum);
    PRINT_STAMP();

    while (1) {
        ptoken = get_token();
        switch (ptoken->type) {
            case (TOKEN_PLUS):
                PRINT_STAMP();
                sum += term();
                printf("in %s sum: %d\n", __func__, sum);
                PRINT_STAMP();
                break;
            case (TOKEN_MINUS):
                sum -= term();
                break;
            case (TOKEN_INVALD):
                PRINT_STAMP();
                return sum;
                break;
            default:
                put_token();
                return sum;
                break;
        }
    }

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
