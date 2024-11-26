# Compiler and flags
CC = gcc
CFLAGS = -Wall

# Source files for main and main2
SRCS_MAIN = main.c json_parser.c notification.c network.c
SRCS_MAIN2 = main2.c json_parser.c notification.c network.c

# Output executables
TARGET_MAIN = main
TARGET_MAIN2 = main2

# Default target
all: $(TARGET_MAIN) $(TARGET_MAIN2)

# Compile and link directly to create the executables
$(TARGET_MAIN):
	$(CC) $(SRCS_MAIN) -o $(TARGET_MAIN) $(CFLAGS) -lcurl

$(TARGET_MAIN2):
	$(CC) $(SRCS_MAIN2) -o $(TARGET_MAIN2) $(CFLAGS) -lcurl

# Clean up the build files
clean:
	rm -f $(TARGET_MAIN) $(TARGET_MAIN2)