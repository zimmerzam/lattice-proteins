CC = g++
CFLAGS = -msse2 -O2 -Wall -std=c++0x -static

EXECUTABLE = saw sequences hamiltonian model density_of_states

all: $(EXECUTABLE)

$(EXECUTABLE):
	$(CC) $(CFLAGS) $@.cpp -o $@

clean:
	rm -f *~

fresh:
	rm -f $(EXECUTABLE) *~
