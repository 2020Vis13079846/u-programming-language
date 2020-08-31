#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

enum token_type {
	tok_eof = -1,
	tok_print = -2,
	tok_read = -3,
	tok_identifier = -4,
	tok_number = -5,
	tok_function = -6,
	tok_string = -7,
	tok_equal = -8,
	tok_and = -9,
	tok_or = -10,
	tok_if = -11,
	tok_while = -12,
	tok_for = -13,
};

int get_token();

int current_token;

int get_next_token() {
	return current_token = get_token();
}

int i = 0;
char *code;

char *string;
char *id;
int value;

int get_token() {
	if (!code[i]) {
		return tok_eof;
	}
	while (code[i] == ' ' || code[i] == '\n') {
		i++;
	}
	if (strncmp(code+i, "//", 2) == 0) {
		while (code[i] && code[i] != '\n' && code[i] != EOF) {
			i++;
		}
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
		while (isdigit(code[i]) || isalpha(code[i])) {
			id[length++] = code[i++];
		}
		printf("%s\n", id);
		if (strcmp(id, "print") == 0) {
			return tok_print;
		}
		if (strcmp(id, "fn") == 0) {
			return tok_function;
		}
		if (strcmp(id, "read") == 0) {
			return tok_read;
		}
		if (strcmp(id, "if") == 0) {
			return tok_if;
		}
		if (strcmp(id, "while") == 0) {
			return tok_while;
		}
		if (strcmp(id, "for") == 0) {
			return tok_for;
		}
		return tok_identifier;
	} else if (isdigit(code[i])) {
		int minus = 1;
		if (code[i-1] == '-') {
			minus = -1;
		}
		value = 0;
		while (isdigit(code[i])) {
			value = value * 10 + (code[i++] - '0');
		}
		value *= minus;
		printf("%d\n", value);
		return tok_number;
	}
	if (strncmp(code+i, "==", 2) == 0) {
		i += 2;
		return tok_equal;
	}
	if (strncmp(code+i, "&&", 2) == 0) {
		i += 2;
		return tok_and;
	}
	if (strncmp(code+i, "||", 2) == 0) {
		i += 2;
		return tok_or;
	}
	return (code[i] ? code[i++] : tok_eof);
}

int main() {
	FILE *file = fopen("test.u", "r");
	int size;
	fseek(file, 0, SEEK_END);
	size = ftell(file);
	rewind(file);
	code = (char *)malloc(sizeof(char)*size);
	fread(code, size-1, sizeof(char), file);
	printf("--- Source code ----------\n");
	printf("%s\n", code);

	printf("--- Lexer ----------------\n");
	get_next_token();
	while (1) {
		if (current_token == tok_eof) {
			break;
		}
		printf("(current_token = %d)\n", current_token);
		get_next_token();
	}
	printf("--------------------------\n");
}
