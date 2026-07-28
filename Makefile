CC      := gcc
CFLAGS  := -Wall -Wextra
TARGET  := program

SRCS := main.c cd.c echo.c ls.c mkdir.c runelf.c utils.c
OBJS := $(SRCS:.c=.o)
HDRS := cd.h echo.h ls.h mkdir.h runelf.h utils.h

.PHONY: all clean run

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $(OBJS)

%.o: %.c $(HDRS)
	$(CC) $(CFLAGS) -c $< -o $@

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(OBJS) $(TARGET)
