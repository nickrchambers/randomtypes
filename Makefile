calc:	y.tab.c lex.yy.c
	cc y.tab.c -lfl -o lang
# older systems used "-ll" to get the "lex" library; "-lfl" gets the "flex" library.

y.tab.c:	lang.y
	yacc --debug --verbose lang.y

lex.yy.c:	lang.l
	lex lang.l
