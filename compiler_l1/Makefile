TARGET = a.out

.PHONY: all clean

all: $(TARGET)

$(TARGET): y.tab.c
	gcc y.tab.c -ly

y.tab.c: translate.y
	yacc translate.y

clean:
	rm -rf y.tab.c a.out

