CC = clang
CFLAGS = -Wall -g
SRCDIR = src
OBJDIR = bin
SRCS := $(wildcard src/*.c) main.c
OBJS := $(SRCS:$(SRCDIR)/%.c=$(OBJDIR)/%.o)
OBJS := $(OBJS:%.c=$(OBJDIR)/%.o)


test:
	echo $(SRCS)
	echo $(OBJS)
setup:
	mkdir ./src ./bin

clean:
	rm -f $(OBJS) main

main: $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	$(CC) $(CFLAGS) -c -o $@ $<

$(OBJDIR)/%.o: %.c
	echo 
	$(CC) $(CFLAGS) -c -o $@ $<

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

