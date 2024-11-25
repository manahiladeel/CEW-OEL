# Compiler and flags
CC = gcc
CFLAGS = -Wall

# Source files for main and main2
SRCS_MAIN = main.c json_parser.c notification.c network.c
SRCS_MAIN2 = main2.c json_parser.c notification.c network.c

# Object files
OBJS_MAIN = $(SRCS_MAIN:.c=.o)
OBJS_MAIN2 = $(SRCS_MAIN2:.c=.o)

# Output executables
TARGET_MAIN = main
TARGET_MAIN2 = main2

# Default target
all: $(TARGET_MAIN) $(TARGET_MAIN2)

# Link the object files to create the executables
$(TARGET_MAIN): $(OBJS_MAIN)
	$(CC) $(OBJS_MAIN) -o $(TARGET_MAIN) $(CFLAGS) -lcurl

$(TARGET_MAIN2): $(OBJS_MAIN2)
	$(CC) $(OBJS_MAIN2) -o $(TARGET_MAIN2) $(CFLAGS) -lcurl

# Compile source files to object files
%.o: %.c
	$(CC) -c $< -o $@ $(CFLAGS)

# Clean up the build files
clean:
	rm -f $(OBJS_MAIN) $(OBJS_MAIN2) $(TARGET_MAIN) $(TARGET_MAIN2)
