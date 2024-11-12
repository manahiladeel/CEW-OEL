# Compiler and flags
CC = gcc
CFLAGS = -Wall -lcurl

# Source files
SRCS = main.c network.c json_parser.c

# Object files
OBJS = $(SRCS:.c=.o)

# Output executable
TARGET = main

# Default target
all: $(TARGET)

# Link the object files to create the executable
$(TARGET): $(OBJS)
	$(CC) $(OBJS) -o $(TARGET) $(CFLAGS)

# Compile source files to object files
%.o: %.c
	$(CC) -c $< -o $@ $(CFLAGS)

# Clean up the build files
clean:
	rm -f $(OBJS) $(TARGET)
