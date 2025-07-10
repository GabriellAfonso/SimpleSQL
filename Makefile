.PHONY: all parser build clean
CC = gcc
CFLAGS = -Iinclude -Wall

SRC = main.c $(wildcard src/*.c) $(wildcard build/parser/*.c)
OUT = bin/simplesql

all: build 

build/parser/parser.tab.c build/parser/parser.tab.h: parser/parser.y 
	mkdir -p build/parser
	bison -d parser/parser.y -o build/parser/parser.tab.c

build/parser/lex.yy.c: parser/lexer.l
	flex -o build/parser/lex.yy.c parser/lexer.l

parser: build/parser/parser.tab.c build/parser/parser.tab.h build/parser/lex.yy.c

build: parser
	mkdir -p bin
	$(CC) $(CFLAGS) $(SRC) -o $(OUT)

clean:
	rm -rf build bin *.o

