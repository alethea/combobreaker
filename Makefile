CC = gcc
PYTHON = python3
CFLAGS = -O2 -Wall -Werror -pedantic -std=gnu99
CPPFLAGS = 
INCLUDES =
LFLAGS = -lOpenCL
TARGET = combobreaker

PASSWORDS_SRC = http://xato.net/files/10k%20most%20common%20with%20frequency.zip
PASSWORDS = passwords.csv

TEMPLATES = $(wildcard *.t)
GENS = $(TEMPLATES:.t=.gen.c)
SRCS = $(wildcard *.c)
OBJS = $(SRCS:.c=.o)
DEPS = $(SRCS:.c=.d)

all: $(TARGET)

$(PASSWORDS):
	wget $(PASSWORDS_SRC) -O- | funzip > $(PASSWORDS)

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

clean:
	rm -f $(TARGET) $(PASSWORDS) *.o *.d *.gen
