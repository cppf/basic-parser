build:
	@flex -o main.yy.cpp main.l
	@bison -o main.tab.cpp -d main.y
	@g++ main.cpp mlib.cpp main.tab.cpp main.yy.cpp -ll

clean:
	@rm -f a.out main.tab.hpp main.tab.cpp main.yy.cpp
