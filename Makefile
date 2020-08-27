all: clean build test

build:
	@gcc main.c -o u

test:
	@./u

clean:
	@rm -f u
