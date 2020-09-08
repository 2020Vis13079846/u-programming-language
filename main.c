#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

enum token_type {
	tok_eof = -1,
	tok_number = -2,
	tok_plus = -3,
	tok_minus = -4
};

struct token {
	int type;
	int value;
};

int i = 0;
char *code;

char *operators[] = {
	"+", "-"
};

/* Lexer */

struct token *get_next_token() {
	struct token *tok = (struct token *)malloc(sizeof(struct token));
	memset(tok, 0, sizeof(struct token));
	tok->type = tok_eof;
	tok->value = 0;
	if (!code[i]) {
		return tok;
	}
	while (code[i] == ' ' || code[i] == '\n') i++;
	if (isdigit(code[i])) {
		int power = 1;
		int f = 0;
		while (isdigit(code[i])) {
			f = f * 10 + (code[i++] - '0');
		}
		tok->type = tok_number;
		tok->value = f;
		return tok;
	}
	for (int j = 0; j < sizeof(operators)/sizeof(char *); j++) {
		if (strncmp(code+i, operators[j], strlen(operators[j])) == 0) {
			tok->type = -(3+j);
			tok->value = (int)code[i];
			i += strlen(operators[j]);
			return tok;
		}
	}
	return tok;
}

/* Parser */

struct token *current_token;

void eat(int token_type) {
	if (current_token->type == token_type) {
		current_token = get_next_token();
	} else {
		printf("(parser) error while parsing\n");
	}
}

int term() {
	struct token *token = current_token;
	eat(tok_number);
	return token->value;
}

int expr() {
	int result = 0;
	struct token *token;
	current_token = get_next_token();
	result = term();
	while (current_token->type == tok_plus || current_token->type == tok_minus) {
		token = current_token;
		if (token->type == tok_plus) {
			eat(tok_plus);
			result = result + term();
		} else if (token->type == tok_minus) {
			eat(tok_minus);
			result = result - term();
		}
	}
	return result;
}

/* Interpreter */

int main(int argc, char *argv[]) {
	/*code = (char *)malloc(sizeof(char)*1024);
	memset(code, 0, sizeof(char)*1024);
	fgets(code, 1024, stdin);
	code[strlen(code)-1] = 0;*/
	code = "12+12";
	current_token = get_next_token();
	printf("--- Source code -------------\n");
	printf("%s\n", code);
	printf("--- Lexer -------------------\n");
	while (current_token->type != tok_eof) {
		printf("%d = '%c'\n", current_token->value, (current_token->type == tok_number ? 0 : current_token->value));
		current_token = get_next_token();
	}
	i = 0;
	printf("--- Parser ------------------\n");
	printf("result = %d\n", expr());
	printf("-----------------------------\n");
	free(current_token);
}
