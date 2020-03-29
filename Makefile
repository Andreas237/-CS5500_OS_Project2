CC=gcc
CFLAGS=-pthread -Wall -I$(IDIR) -D_GNU_SOURCE



ODIR=odir
IDIR=include




_DEPS = task1.h task2.h
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))



_OBJ = main.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))





$(ODIR)/%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)


exec_p2: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)






.PHONY: clean

clean:
	rm exec_p2 $(ODIR)/*.o
