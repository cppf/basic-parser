build:
	@flex scanner.l
	@bison -d parser.y
	@gcc -o main main.c parser.tab.c lex.yy.c -lfl

clean:
	@rm -f main parser.tab.h parser.tab.c lex.yy.c
