TARGET = a.out

.PHONY: all clean

all: $(TARGET)

$(TARGET): yacc.tab.c
	gcc yacc.tab.c -ly -ll

yacc.tab.c: yacc.c
	flex lex.l
	bison yacc.y

clean:
	rm -rf yacc.tab.c a.out lex.yy.c

