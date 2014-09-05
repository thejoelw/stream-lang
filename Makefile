# Makefile

FILES   = Lexer.cpp Parser.cpp main.c astexpr.cpp astapply.cpp astflow.cpp astblock.cpp astident.cpp astnumber.cpp bignum.cpp stream.cpp
CC  = clang++

CFLAGS  = -g -std=c++11 -Wfatal-errors -lgmp `llvm-config --cppflags --ldflags --libs core`

all:		stream-lang
			

stream-lang:		$(FILES)
			$(CC) $(CFLAGS) $(FILES) -o stream-lang

Lexer.cpp:	Lexer.l 
			flex Lexer.l

Parser.cpp:	Parser.y Lexer.cpp
			bison Parser.y

clean:
			rm -f *.o *~ Lexer.cpp Lexer.h Parser.cpp Parser.h stream-lang
