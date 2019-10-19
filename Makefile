build:
	@flex scanner.l
	@bison -d parser.y
	@gcc -o parser lex.yy.c parser.tab.c -lfl

clean:
	@rm -f lex.yy.c parser.tab.h parser.tab.c
	@rm -f scanner parser
