CC=gcc
CFLAGS=-pthread -Wall -I$(IDIR) -D_GNU_SOURCE



ODIR=odir
IDIR=include




_DEPS = task1.h task2.h task3.h
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))



_OBJ = main.o 
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))





$(ODIR)/%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

all: exec_p2 task3

exec_p2: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)


task3: list-forming.c
	$(CC) -o $@ $^ $(CFLAGS)



.PHONY: clean

clean:
	rm exec_p2 $(ODIR)/*.o task3
