CC=gcc
CFLAGS=-Wall -Wextra
LDLIBS=-ll

main: main.o lex.yy.o parser.tab.o weed.h weed.o tree.h tree.o pretty.h pretty.o
	$(CC) $(CFLAGS) main.o lex.yy.o parser.tab.o weed.o tree.o pretty.o -o golitec $(LDLIBS)

parser.tab.c parser.tab.h: golite.y
	bison --yacc --defines=parser.tab.c --output=parser.tab.h golite.y

lex.yy.c: golite.l parser.tab.h
	flex golite.l

.PHONY : clean
clean:
	rm -f parser.tab.* lex.yy.* *.o golitec
