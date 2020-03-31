SOURCE = $(wildcard *.c)
TARGETS = $(patsubst %.c, %, $(SOURCE))

CC = gcc


CFLAGS = -Wall -g -lGL -lGLU -lglut -DOS_LINUX

all:$(TARGETS)
#all:
#	gcc -o hello.o hello.c -lGL -lGLU -lglut
$(TARGETS):%:%.c
	$(CC) $< $(CFLAGS) -o $@

.PHONY:clean all
clean:
	-rm -rf $(TARGETS)
