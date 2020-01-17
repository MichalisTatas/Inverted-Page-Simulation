CC = gcc
CFLAGS = -g3 -Wall
LDFLAGS = -lm

BDIR = bin
ODIR = build
IDIR = include
SDIR = src

EXECUTABLE = runner

_DEPS = InvertedPageTable.h WS.h LRU.h Simulator.h queue.h
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ = main.o InvertedPageTable.o WS.o LRU.o Simulator.o queue.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

$(ODIR)/%.o: $(SDIR)/%.c $(DEPS)
	$(CC) $(CFLAGS) -c $< -o $@ $(LDFLAGS)

$(BDIR)/$(EXECUTABLE): $(OBJ)
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)

.PHONY: clean run

run:
	./$(BDIR)/$(EXECUTABLE) -a LRU -f 100 -q 10 -m 10

valgrind:
	valgrind ./$(BDIR)/$(EXECUTABLE) -a LRU -f 10 -q 10 -m 10

clean:
	rm -f $(ODIR)/*.o
	rm -f $(BDIR)/$(EXECUTABLE)