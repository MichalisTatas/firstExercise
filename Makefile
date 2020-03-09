CC = gcc
CFLAGS = -g3 -Wall
LDFLAGS = 

BDIR = bin
ODIR = build
IDIR = include
SDIR = source

EXECUTABLE = main

_DEPS = hashTable.h
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ = main.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

$(ODIR)/%.o: $(SDIR)/%.c $(DEPS)
	$(CC) $(CFLAGS) -c $< -o $@ $(LDFLAGS)

$(BDIR)/$(EXECUTABLE): $(OBJ)
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)

.PHONY: clean run valgrind

run:
	./$(BDIR)/$(EXECUTABLE) -p small.txt -h1 10 -h2 15 -b 23

valgrind:
	valgrind --leak-check=full ./$(BDIR)/$(EXECUTABLE) -p small.txt -h1 10 -h2 15 -b 23

clean:
	rm -f $(ODIR)/*.o
	rm -f $(BDIR)/$(EXECUTABLE)