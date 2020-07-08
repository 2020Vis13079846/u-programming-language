all: clean build test

build:
	bison parser.y
	flex scanner.lex
	g++ lex.yy.c -lfl -o sunflower

test:
	./sunflower test.sfl

clean:
	rm -rf parser.tab.c lex.yy.c sunflower 
