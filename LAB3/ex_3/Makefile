TARGET = ex_3
TARGET_SOURCES = ex_3.c

FLAGS = -O2 -Wall -MMD
LIBS = -lwiringPi

CMP = gcc
LDFLAGS = $(LIBS)

all: $(TARGET) clean

$(TARGET): ex_3.o
    $(CMP) $(FLAGS) -o $@ $^ $(LDFLAGS)

%.o: %.c
    $(CMP) $(FLAGS) -c -o $@ $
