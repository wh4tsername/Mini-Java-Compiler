all: mini-java

mini-java.tab.c mini-java.tab.h: ../interpreter/parser.y
	bison -d mini-java.y

lex.yy.c: ../interpreter/mini-java.l
	flex mini-java.l

mini-java: ../interpreter/lex.yy.c mini-java.tab.c main.cpp
	g++ -std=c++17 lex.yy.c mini-java.tab.c main.cpp -o mini-java
