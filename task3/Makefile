CC=gcc
CFLAGS=-g -pthread -D_GNU_SOURCE
OBJ=list-forming.o
EXEC=list-forming

%.o: %.c
	$(CC) -c -o $@ $< $(CFLAGS)



$(EXEC): $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)


.PHONY: clean

clean:
	rm *.o $(EXEC)
