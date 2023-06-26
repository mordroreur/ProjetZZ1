CC=gcc

LDFLAGS=$(shell sdl2-config --cflags --libs) -lm -lSDL2_ttf -lpthread -D_REENTRANT -lSDL2_image
CFLAGS=-Wall $(shell sdl2-config --cflags --libs) -MMD

EXEC=res
SRC=$(wildcard *.c)
OBJ=$(SRC:.c=.o)
DEPS := $(SRC:.o=.d)


all:$(EXEC)

$(EXEC):$(OBJ)
	$(CC) -o $@ $^ $(LDFLAGS)

%.o:%.c
	$(CC) -o $@ -c $< $(CFLAGS)

-include $(DEPS)

.PHONY:clean mrproper

clean:
	rm -rf *.o

mrproper: clean
	rm -rf $(EXEC)
	rm -rf compile_commands.json
	rm -rf .clangd

clangd: clean
	bear make
