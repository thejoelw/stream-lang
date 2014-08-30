# Makefile

FILES	= Lexer.c Parser.c main.c astexpr.cpp astapply.cpp astflow.cpp astfunction.cpp astident.cpp astnumber.cpp bignum.cpp
CC	= clang++

CFLAGS	= -g -std=c++11 -lgmp `llvm-config --cppflags --ldflags --libs core`

all:		$(FILES)
			$(CC) $(CFLAGS) $(FILES) -o all

Lexer.c:	Lexer.l 
			flex Lexer.l

Parser.c:	Parser.y Lexer.c
			bison Parser.y

clean:
			rm -f *.o *~ Lexer.c Lexer.h Parser.c Parser.h all
