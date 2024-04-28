TARGET = ex_4
TARGET_SOURCES = ex_4.c

FLAGS = -O2 -Wall -MMD
LIBS = -lwiringPi

CMP = gcc
LDFLAGS = $(LIBS)

all: $(TARGET) clean

$(TARGET): $(TARGET_SOURCES:.c=.o)
    $(CMP) $(FLAGS) -o $@ $^ $(LDFLAGS)

%.o: %.c
    $(CMP) $(FLAGS) -c -o $@ $
