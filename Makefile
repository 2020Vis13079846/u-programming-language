all: clean build test

build:
	@bison parser.y
	@flex scanner.lex
	@g++ lex.yy.c -lfl -o universe

test:
	@./sunflower test.u

clean:
	@rm -rf parser.tab.c lex.yy.c universe 
