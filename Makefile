build:
	@flex main.l
	@bison -d main.y
	@g++ main.cpp mrun.cpp main.tab.c lex.yy.c -ll

clean:
	@rm -f a.out main.tab.h main.tab.c lex.yy.c
