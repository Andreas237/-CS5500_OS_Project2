CC=gcc
CFLAGS=-g -pthread -D_GNU_SOURCE
OBJ=my_list-forming.o
EXEC=my_list-forming

%.o: %.c
	$(CC) -c -o $@ $< $(CFLAGS)



$(EXEC): $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)


.PHONY: clean

clean:
	rm *.o $(EXEC)
