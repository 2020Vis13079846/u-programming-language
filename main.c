#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

enum token_type {
	tok_eof = 1,
	tok_print = 2,
	tok_read = 3,
	tok_identifier = 4,
	tok_number = 5,
	tok_function = 6,
	tok_string = 7
};

char *code;
int i = 0;

int get_token() {
	if (!code[i]) {
		return tok_eof;
	}
	while (code[i] == ' ' || code[i] == '\n') {
		i++;
	}
	if (i < strlen(code)-1) {
		if (code[i] == '/' && code[i+1] == '/') {
			while (code[i] && code[i] != '\n' && code[i] != EOF) {
				i++;
			}
			return get_token();
		}
	}
	if (code[i] == '"') {
		char *string = (char *)malloc(sizeof(char)*1024);
		int length = 0;
		do {
			string[length++] = code[i++];
		} while (code[i] != '"');
		i++;
		string[length] = '"';
		//printf("%s\n", string);
		return tok_string;
	}
	if (isalpha(code[i])) {
		char *id = (char *)malloc(sizeof(char)*1024);
		int length = 0;
		while (isdigit(code[i]) || isalpha(code[i])) {
			id[length++] = code[i++];
		}
		//printf("%s\n", id);
		if (strcmp(id, "print") == 0) {
			return tok_print;
		}
		if (strcmp(id, "fn") == 0) {
			return tok_function;
		}
		if (strcmp(id, "read") == 0) {
			return tok_read;
		}
		return tok_identifier;
	} else if (isdigit(code[i])) {
		int value = 0;
		while (isdigit(code[i])) {
			value = value * 10 + (code[i++] - '0');
		}
		//printf("%d\n", value);
		return tok_number;
	}
	return code[i++];
}

int main() {
	FILE *file = fopen("test.u", "r");
	int size;
	fseek(file, 0, SEEK_END);
	size = ftell(file);
	rewind(file);
	code = (char *)malloc(sizeof(char)*size);
	fread(code, size, sizeof(char), file);
	code[size] = 0;
	while (code[i]) {
		printf("(token_type = %d)\n", get_token());
	}
}
