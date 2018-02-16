CC=gcc
CFLAGS=-Wall -Wextra
LDLIBS=-lfl

main: parser.tab.o lex.yy.o main.o tree.h tree.o pretty.h pretty.o symbol.h symbol.o type.h type.o codegen.h codegen.o
	$(CC) $(CFLAGS) lex.yy.o parser.tab.o tree.o symbol.o type.o codegen.o pretty.o main.o -o golitec $(LDLIBS)

parser.tab.c parser.tab.h: golite.y
	bison --yacc --defines=parser.tab.c --output=parser.tab.h golite.y

lex.yy.c: golite.l parser.tab.h
	flex golite.l

.PHONY : clean
clean:
	rm -f parser.tab.* lex.yy.* *.o golitec
