all: clean build test

build:
	@gcc main.c -o universe

test:
	@./universe test.u

clean:
	@rm -rf parser.tab.c lex.yy.c universe
