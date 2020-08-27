#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

struct token {
	int type;
	int attribute;
};

enum {
	OPERATOR1,
	OPERATOR2,
	ASSIGN,
	SEMICOLON,
	NUMBER,
	ID,
} type;

enum {
	ADD,
	SUB,
	MUL,
	DIV,
} attribute;

char *symbols[1024];
int size = 0;

struct token *lexer(char *text) {
	struct token token;
	for (int i = 0; i < strlen(text); i++) {
		if (text[i] == ' ' || text[i] == '\n') {
			continue;
		}
		if (text[i] == '+') {
			token.type = OPERATOR1;
			token.attribute = ADD;
		} else if (text[i] == '-') {
			token.type = OPERATOR1;
			token.attribute = SUB;
		} else if (text[i] == '*') {
			token.type = OPERATOR2;
			token.attribute = MUL;
		} else if (text[i] == '/') {
			token.type = OPERATOR2;
			token.attribute = DIV;
		} else if (text[i] == '=') {
			token.type = ASSIGN;
		} else if (text[i] == ';') {
			token.type = SEMICOLON;
		} else {
			if (isalpha(text[i])) {
				char *id = (char *)malloc(sizeof(char)*1024);
				int length = 0;
				while (isdigit(text[i]) || isalpha(text[i])) {
					id[length++] = text[i++];
				}
				symbols[size] = id;
				token.type = ID;
				token.attribute = size;
				size++;
			} else if (isdigit(text[i])) {
				int value = 0;
				while (isdigit(text[i])) {
					value = value * 10 + (text[i] - '0');
					i++;
				}
				token.type = NUMBER;
				token.attribute = value;
			}
			i--;
		}
		printf("(struct token type=%d attribute=%d)\n", token.type, token.attribute);
	}
}

int main() {
	char *code = "abc = 12 + 23 * 1;";
	lexer(code);
}
