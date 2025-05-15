# Compiler to use
CC = gcc

# Compiler flags
CFLAGS = -Wall -Wextra -g

# Target executable name
TARGET = http_server

# Source files
SRCS = server.c handle_html.c

# Object files
OBJS = $(SRCS:.c=.o)

# Default target
all: $(TARGET)

# Rule to build the executable
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

# Rule to build object files from source files
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Clean target
clean:
	rm -f $(OBJS) $(TARGET)

# Run target (optional)
run: $(TARGET)
	./$(TARGET)

# Phony targets
.PHONY: all clean run
