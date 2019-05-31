
CC=gcc
CFLAGS=-Wall -c -g
PROGNAME=ohm
OBJECTS= main.o cmnCmdOptions2.o 

main: $(OBJECTS)
	$(CC) -o $(PROGNAME) $(OBJECTS) -lm

cmnCmdOptions2.o: cmnCmdOptions2.c  cmnCmdOptions2.h
	$(CC) $(CFLAGS) cmnCmdOptions2.c
        
main.o: main.c main.h
	$(CC) $(CFLAGS) main.c

.PHONY : clean
clean:
	rm *.o $(PROGNAME)

.PHONY : run
run: all
	./$(PROGNAME)

