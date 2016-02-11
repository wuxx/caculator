#include <stdio.h>

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

struct __token__ token_pool[1024];

int expect()
{

}

int get_token()
{

}

int factor()
{
}

int term()
{
}

int expr(char *exp)
{
    int sum = 0;

    return sum;
}

int main(int argc, char **argv)
{
    int i, sum;
    char *exp;

    if (argc != 2) {
        printf("%s \"expression\"\n", argv[0]);
        return -1;
    }

    /* init */
    exp = argv[1];
    for(i=0;i<sizeof(token_pool)/sizeof(token_pool[0]);i++) {
        token_pool[i].type = TOKEN_INVALD;
    }

    printf("expr: %s\n", exp);
    sum = expr(exp);
    printf("sum: %d\n", sum);
    return 0;
}
