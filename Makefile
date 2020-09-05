all: clean build test

build:
	@mkdir -p build
	@gcc main.c -o ./build/u

test:
	@./build/u

clean:
	@rm -fr ./build
