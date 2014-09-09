# Makefile

FILES = main.c astapply.cpp astblock.cpp astexpr.cpp astflow.cpp astident.cpp astnumber.cpp astsame.cpp bignum.cpp closure.cpp context.cpp Lexer.cpp number.cpp object.cpp Parser.cpp stream.cpp
CC = clang++
CFLAGS = -g -std=c++11 -Wfatal-errors -lgmp `llvm-config --cppflags --ldflags --libs core`

all:		stream-lang
			

stream-lang:		$(FILES)
			$(CC) $(CFLAGS) $(FILES) -o stream-lang

Lexer.cpp:	Lexer.l 
			flex Lexer.l

Parser.cpp:	Parser.y Lexer.cpp
			bison Parser.y

clean:
			rm -f *.o *~ Lexer.cpp Lexer.h Parser.cpp Parser.h stream-lang
