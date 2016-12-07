all: Parser Scanner Driver AST Hash
	gcc parser.tab.o lex.yy.o driver.o ast.o openhash.o -o bcc

Driver: driver.o

AST: ast.o

Hash: openhash.o

Scanner: lexer.lex
	flex lexer.lex		
	gcc -c lex.yy.c

Parser: parser.y
	bison -d parser.y
	gcc -c parser.tab.c

%.o: %.c
	gcc -c $<
