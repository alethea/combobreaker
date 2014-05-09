CC = gcc
PYTHON = python3
CFLAGS = -O2 -Wall -Werror -pedantic -std=gnu99
CPPFLAGS = 
INCLUDES =
LFLAGS = -lOpenCL
TARGET = combobreaker
PASSWORDS = passwords.csv

TEMPLATES = $(wildcard *.t)
GENS = $(TEMPLATES:.t=.gen.c)
SRCS = $(wildcard *.c) $(GENS)
OBJS = $(SRCS:.c=.o)
DEPS = $(SRCS:.c=.d)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC)  -o $@ $^ $(CFLAGS) $(LFLAGS)

-include $(DEPS)

.c.o:
	$(CC)  -o $@ -c $< $(CFLAGS) $(INCLUDES) $(CPPFLAGS)

%.d: %.c
	$(CC) -MF $@ -MM $< $(CFLAGS) $(INCLUDES) $(CPPFLAGS)

%.gen.c: %.py %.t $(PASSWORDS)
	$(PYTHON) $^ $@

.PHONY: clean

.SECONDARY: $(GENS)

clean:
	rm -f $(TARGET) *.o *.d *.gen.c
