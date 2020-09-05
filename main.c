#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

enum token_type {
	tok_eof = -1,
	tok_identifier = -2,
	tok_number = -3,
	tok_real = -4,
	tok_string = -5,
	tok_print = -6,
	tok_read = -7,
	tok_function = -8,
	tok_if = -9,
	tok_while = -10,
	tok_for = -11,
	tok_else = -12,
	tok_return = -13,
	tok_equal = -14,
	tok_and = -15,
	tok_or = -16,
	tok_left_paren = -17,
	tok_right_paren = -18,
	tok_assign = -19,
	tok_semicolon = -20,
	tok_add = -21,
	tok_sub = -22,
	tok_mul = -23,
	tok_div = -24,
	tok_less = -25,
	tok_great = -26,
	tok_less_equal = -27,
	tok_great_equal = -28,
	tok_left_bracket = -29,
	tok_right_bracket = -30
};

struct token {
	int type;
	union {
		int i;
		char *s;
		float f;
	} v;
};

int get_token();

int current_token;

int get_next_token() {
	return current_token = get_token();
}

char *keywords[] = {
	"print", "read", "fn", "if", "while", "for",
	"else", "return"
};

char *operators[] = {
	"==", "&&", "||", "(", ")", "=", ";", "+",
	"-", "*", "/", "<", ">", "<=", ">=", "{",
	"}"
};

int i = 0;
char *code;

char *string;
char *id;
int value;

int get_token() {
	if (!code[i]) {
		return tok_eof;
	}
	while (code[i] == ' ' || code[i] == '\n') i++;
	if (strncmp(code+i, "//", 2) == 0) {
		while (code[i] && code[i] != '\n' && code[i] != EOF) i++;
		return get_token();
	}
	if (code[i] == '"') {
		string = (char *)malloc(sizeof(char)*1024);
		int length = 0;
		do {
			string[length++] = code[i++];
		} while (code[i] != '"');
		string[length] = code[i++];
		printf("%s\n", string);
		return tok_string;
	}
	if (isalpha(code[i])) {
		id = (char *)malloc(sizeof(char)*1024);
		int length = 0;
		while (isdigit(code[i]) || isalpha(code[i]) || code[i] == '_') {
			id[length++] = code[i++];
		}
		printf("%s\n", id);
		for (int j = 0; j < sizeof(keywords)/sizeof(char *); j++) {
			if (strcmp(id, keywords[j]) == 0) {
				return -(j+6);
			}
		}
		return tok_identifier;
	}
	if (isdigit(code[i])) {
		int power = 1;
		float f = 0;
		while (isdigit(code[i])) {
			f = f * 10 + (code[i++] - '0');
		}
		if (code[i] == '.') {
			i++;
			while (isdigit(code[i])) {
				f = f * 10 + (code[i++] - '0');
				power *= 10;
			}
			f /= power;
		}
		printf("%.6f\n", f);
		return (f == (int)f ? tok_number : tok_real);
	}
	for (int j = 0; j < sizeof(operators)/sizeof(char *); j++) {
		if (strncmp(code+i, operators[j], strlen(operators[j])) == 0) {
			i += strlen(operators[j]);
			return -(j+14);
		}
	}
	return (code[i] ? code[i++] : tok_eof);
}

int main(int argc, char *argv[]) {
	FILE *file = fopen("test.u", "r");
	int size;
	fseek(file, 0, SEEK_END);
	size = ftell(file);
	rewind(file);
	code = (char *)malloc(sizeof(char)*size);
	fread(code, size-1, sizeof(char), file);
	printf("--- Source code -------------\n");
	printf("%s\n", code);
	printf("--- Lexer -------------------\n");
	get_next_token();
	while (1) {
		if (current_token == tok_eof) {
			break;
		}
		printf("(current_token = %d [i = %d])\n", current_token, i);
		get_next_token();
	}
	printf("-----------------------------\n");
}
