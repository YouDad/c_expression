CC := g++

.PHONY: cly

cly: lex.yy.c yacc.tab.c obj
	g++ -g *.o -o cly
	make clean

.PHONY: obj

obj: lex.yy.o yacc.tab.o grammer.o lexical.o

lex.yy.c: lex.l
	flex lex.l

yacc.tab.c: yacc.y
	bison -Wcex -d yacc.y

clean:
	rm -f lex.yy.c
	rm -f yacc.tab.c
	rm -f yacc.tab.h
	rm -f yacc.c
	rm -f *.o
