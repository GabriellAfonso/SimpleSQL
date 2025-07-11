.PHONY: all parser build clean
CC = gcc
CFLAGS = -Iinclude -Wall

SRC = src/main.c $(wildcard src/database/*.c) $(wildcard build/parser/*.c)
OUT = bin/simplesql
LIB = $(wildcard libs/*.a)

all: build 

build/parser/parser.tab.c build/parser/parser.tab.h: src/parser/parser.y 
	mkdir -p build/parser
	bison -d src/parser/parser.y -o build/parser/parser.tab.c

build/parser/lex.yy.c: src/parser/lexer.l
	flex -o build/parser/lex.yy.c src/parser/lexer.l

parser: build/parser/parser.tab.c build/parser/parser.tab.h build/parser/lex.yy.c

build: parser
	mkdir -p bin
	$(CC) $(CFLAGS) $(SRC) $(LIB) -o $(OUT)

clean:
	rm -rf build bin *.o

run:
	./$(OUT)
