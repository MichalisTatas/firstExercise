CC = gcc
CFLAGS = -g3 -Wall
LDFLAGS = 

BDIR = bin
ODIR = build
IDIR = include
SDIR = source

EXECUTABLE = main

_DEPS = hashTable.h patient.h avlTree.h binaryHeap.h queue.h diseaseMonitor.h
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ = main.o hashTable.o patient.o avlTree.o binaryHeap.o queue.o diseaseMonitor.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

$(ODIR)/%.o: $(SDIR)/%.c $(DEPS)
	$(CC) $(CFLAGS) -c $< -o $@ $(LDFLAGS)

$(BDIR)/$(EXECUTABLE): $(OBJ)
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)

.PHONY: clean run valgrind

run:
	./$(BDIR)/$(EXECUTABLE) -p small.txt -h1 10 -h2 10 -b 24

valgrind:
	valgrind --leak-check=full ./$(BDIR)/$(EXECUTABLE) -p small.txt -h1 10 -h2 10 -b 24

clean:
	rm -f $(ODIR)/*.o
	rm -f $(BDIR)/$(EXECUTABLE)