#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

enum token_type {
	tok_eof = 1,
	tok_print = 2,
	tok_identifier = 3,
	tok_number = 4,
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
	if (code[i] == '#') {
		while (code[i] && code[i] != '\n' && code[i] != EOF) {
			i++;
		}
		return get_token();
	}
	if (isalpha(code[i])) {
		char *id = (char *)malloc(sizeof(char)*1024);
		int length = 0;
		while (isdigit(code[i]) || isalpha(code[i])) {
			id[length++] = code[i++];
		}
		if (strcmp(id, "print") == 0) {
			return tok_print;
		}
		return tok_identifier;
	} else if (isdigit(code[i])) {
		int value = 0;
		while (isdigit(code[i])) {
			value = value * 10 + (code[i++] - '0');
		}
		return tok_number;
	}
        i++;
	return code[i-1];
}

int main() {
	code = "print (1);";
	while (code[i]) {
		printf("(token_type = %d)\n", get_token());
	}
}
