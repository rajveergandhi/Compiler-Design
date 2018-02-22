CC=gcc
CFLAGS=-Wall -Wextra
LDLIBS=-lfl

main: main.o lex.yy.o parser.tab.o tree.h
	$(CC) $(CFLAGS) main.o lex.yy.o parser.tab.o -o golitec $(LDLIBS)

parser.tab.c parser.tab.h: golite.y
	bison --yacc --defines=parser.tab.c --output=parser.tab.h golite.y

lex.yy.c: golite.l parser.tab.h
	flex golite.l

.PHONY : clean
clean:
	rm -f parser.tab.* lex.yy.* *.o golitec
