CC=gcc
CFLAGS=-Wall -Wextra
LDLIBS=-ll

main: main.o lex.yy.o parser.tab.o tree.h tree.o weed.h weed.o weed2.h weed2.o pretty.h pretty.o symbol.h symbol.o type.h type.o codegen.h codegen.o
	$(CC) $(CFLAGS) main.o lex.yy.o parser.tab.o tree.o weed.o weed2.o pretty.o symbol.o type.o codegen.o -o golitec $(LDLIBS)

parser.tab.c parser.tab.h: golite.y
	bison --yacc --defines=parser.tab.c --output=parser.tab.h golite.y

lex.yy.c: golite.l parser.tab.h
	flex golite.l

.PHONY : clean
clean:
	rm -f parser.tab.* lex.yy.* *.o golitec
