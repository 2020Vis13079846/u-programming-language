/*
 * Copyright (c) 2020 Simon Chaykin.
 * All rights reserved.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

typedef enum _token_type {
    tok_eof = -1,
    tok_number = -2,
    tok_plus = -3,
    tok_minus = -4,
    tok_mul = -5,
    tok_div = -6,
    tok_lparen = -7,
    tok_rparen = -8,
    tok_lbrace = -9,
    tok_rbrace = -10,
    tok_less = -11,
    tok_greater = -12,
    tok_equal = -13,
    tok_not_equal = -14,
    tok_less_equal = -15,
    tok_greater_equal = -16,
    tok_not = -17,
    tok_and = -18,
    tok_or = -19,
    tok_comma = -20,
    tok_dot_comma = -21 /* maybe for C-style (idk) */
} token_type;

typedef struct _token {
    int type;
    int value;
} token;

int i;
char *code;

char *operators[] = {
    "+", "-", "*", "/", "(", ")", "{", "}", "<",
    ">", "==", "!=", "<=", ">=", "!", "&&", "||",
    ",", ";"
};

/* Lexer */

token *get_next_token()
{
    unsigned long j;
    int value;
    token *tok = (token *)malloc(sizeof(token));
    memset(tok, 0, sizeof(token));
    tok->type = tok_eof;
    tok->value = 0;

    if (!code[i])
    {
        return tok;
    }

    while (code[i] == ' ' || code[i] == '\n')
    {
        i++;
    }

    if (isdigit(code[i]))
    {
        value = 0;
        while (isdigit(code[i]))
        {
            value = value * 10 + (code[i++] - '0');
        }
        tok->type = tok_number;
        tok->value = value;
        return tok;
    }

    for (j = 0; j < sizeof(operators)/sizeof(char *); j++)
    {
        if (strncmp(code+i, operators[j], strlen(operators[j])) == 0)
        {
            tok->type = -(3+j);
            tok->value = (int)code[i];
            i += strlen(operators[j]);
            return tok;
        }
    }
    return tok;
}

/* Parser */

token *current_token;

int factor();
int term();
int expr();

void eat(tok_type)
    int tok_type;
{
    if (current_token->type == tok_type)
    {
        current_token = get_next_token();
        return;
    }
    printf("(parser) error while parsing\n");
    exit(1);
}

int factor()
{
    int result;
    token *tok = current_token;
    if (tok->type == tok_number)
    {
        eat(tok_number);
        return tok->value;
    }
    if (tok->type == tok_lparen)
    {
        eat(tok_lparen);
        result = expr();
        eat(tok_rparen);
        return result;
    }
    printf("(parser) error in factor\n");
    exit(2);
}

int term()
{
    token *tok;
    int result = factor();
    while (current_token->type == tok_mul || current_token->type == tok_div)
    {
        tok = current_token;
        if (tok->type == tok_mul)
        {
            eat(tok_mul);
            result = result * factor();
        }
        else if (tok->type == tok_div)
        {
            eat(tok_div);
            result = result / factor();
        }
    }
    return result;
}

int expr()
{
    int result = 0;
    token *tok;
    result = term();
    while (current_token->type == tok_plus || current_token->type == tok_minus)
    {
        tok = current_token;
        if (tok->type == tok_plus)
        {
            eat(tok_plus);
            result = result + term();
        }
        else if (tok->type == tok_minus)
        {
            eat(tok_minus);
            result = result - term();
        }
    }
    return result;
}

/* Interpreter */

int main()
{
    code = "1 * 0";
    i = 0;
    current_token = get_next_token();
    printf("result = %d\n", expr());
    return 0;
}
