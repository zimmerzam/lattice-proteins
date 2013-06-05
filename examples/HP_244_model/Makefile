CC = g++46
CFLAGS = -msse2 -O2 -Wall -std=c++0x -static

EXECUTABLE = HP_244_model

all: $(EXECUTABLE)

$(EXECUTABLE):
	$(CC) $(CFLAGS) $@.cpp -o $@

clean:
	rm -f *~

fresh:
	rm -f $(EXECUTABLE) *~
