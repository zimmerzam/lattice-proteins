CC = g++
CFLAGS = -msse2 -O2 -Wall

EXECUTABLE = structures fold density_of_states statistics

all: $(EXECUTABLE)

$(EXECUTABLE):
	$(CC) $(CFLAGS) $@.cpp -o $@

clean:
	rm -f *~

fresh:
	rm -f $(EXECUTABLE) *~
