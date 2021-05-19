TARGET = rb_tree

.PHONY: all clear

all: $(TARGET)

$(TARGET):
	g++ main.cpp -o $(TARGET)
	./$(TARGET)
	gnuplot plot.plt

clear:
	rm $(TARGET) *.dat *.svg