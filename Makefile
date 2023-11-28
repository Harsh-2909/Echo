# Use TABS instead of Spaces for indentation. I spent 20mins banging my head to find the issue
# Compiler to use
CC = gcc

# Compiler flags
CFLAGS = -lpthread -Wall

# Name of the output file
TARGET = server

# Source files
SOURCES = ./src/server.c

all: $(TARGET)

$(TARGET): $(SOURCES)
	$(CC) $(SOURCES) -o $(TARGET) $(CFLAGS)

clean:
	rm -f $(TARGET)