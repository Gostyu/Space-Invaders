EXEC=space
SOURCES=carte.c main.c cpycarte.c mouvement.c
OBJECTS=$(SOURCES:.c=.o)
CC=gcc
CFLAGS= -Wall -std=gnu99 -Werror
 
.PHONY: default clean
 
default: $(EXEC)
 
main.o: carte.c carte.h cpycarte.c cpycarte.h mouvement.c mouvement.h

%.o: %.c
	$(CC) $< $(CFLAGS) -o $@ -c 
 
$(EXEC): $(OBJECTS)
	$(CC) -o $@ $^
 
clean:
	rm -rf $(EXEC) $(OBJECTS) $(SOURCES:.c=.c~) $(SOURCES:.c=.h~) Makefile~
