CC = gcc
CFLAGS = -O2 -Wall -Werror -pedantic -std=gnu99
CPPFLAGS = 
INCLUDES =
LFLAGS = -lOpenCL
TARGET = combobreaker

PASSWORDS_SRC = http://xato.net/files/10k%20most%20common%20with%20frequency.zip
PASSWORDS = passwords.csv

SRCS := $(wildcard *.c)
OBJS = $(SRCS:.c=.o)
DEPS = $(SRCS:.c=.d)

$(PASSWORDS):
	wget $(PASSWORDS_SRC) -O- | funzip > $(PASSWORDS)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC)  -o $@ $^ $(CFLAGS) $(LFLAGS)

-include $(DEPS)

.c.o:
	$(CC)  -o $@ -c $< $(CFLAGS) $(INCLUDES) $(CPPFLAGS)

%.d: %.c
	$(CC) -MF $@ -MM $< $(CFLAGS) $(INCLUDES) $(CPPFLAGS)

.PHONY: clean

clean:
	rm -f $(TARGET) $(PASSWORDS) *.o *.d
