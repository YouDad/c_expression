.PHONY: default
default: compile

.PHONY: compile
compile: lex yacc $(objs)
	$(CC) $(CPPFLAGS) main.c $(objs) -o c_expression

.PHONY: lex
lex:
	flex lex.l
	mv lex.yy.c $(OUTDIR)/

.PHONY: yacc
yacc:
	bison -d yacc.y
	mv yacc.tab.c $(OUTDIR)/
	mv yacc.tab.h $(OUTDIR)/

.PHONY: install
install:
	mv c_expression $(OUTDIR)/
