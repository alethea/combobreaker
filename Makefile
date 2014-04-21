CC = gcc
CFLAGS = -O2 -Wall -Werror -pedantic -std=c99
CPPFLAGS = 
INCLUDES =
LFLAGS = -lOpenCL
TARGET = combobreaker

SRCS := $(wildcard *.c)
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

.PHONY: clean

clean:
	rm -f $(TARGET) *.o *.d
