#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "caculator.h"

int expr_dc();

int factor()
{
    int sum;
    struct __token__ *ptoken;
    ptoken = get_next_token();
    switch (ptoken->type) {
        case (TOKEN_INTEGER):
            sum = ptoken->value;
            return sum;
            break;
        case (TOKEN_LPAREN):
            sum = expr_dc();
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

    sum = factor();


    while (1) {
        ptoken = get_next_token();
        switch (ptoken->type) {
            case (TOKEN_MUL):
                sum *= factor();
                break;
            case (TOKEN_DIV):
                sum /= factor();
                break;
            case (TOKEN_INVALID):
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

int expr_dc()
{
    int sum = 0;
    struct __token__ *ptoken;
    sum = term();

    while (1) {
        ptoken = get_next_token();
        switch (ptoken->type) {
            case (TOKEN_PLUS):
                sum += term();
                break;
            case (TOKEN_MINUS):
                sum -= term();
                break;
            case (TOKEN_INVALID):
                return sum;
                break;
            default:
                put_token();
                return sum;
                break;
        }
    }
}

