# ========================
# C-Minesweeper Makefile
# ========================

# Compiler and flags
CC = gcc
CFLAGS = -g -Wall -fdiagnostics-color=always

# Name of the final executable
TARGET = main

# Source files for modules
SRCS = minesweeper/main.c \
       minesweeper/game/game.c \
       minesweeper/game/board/board.c \
       minesweeper/game/graphics/graphic_printer.c \
	   minesweeper/game/sysconf/sysconf.c

# Object files
OBJS = $(SRCS:.c=.o)

# ======================================
# Default target: build the executable
# ======================================
all: $(TARGET)

# Link all object files into the final binary
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

# Compile each .c file into a .o object file
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# ================================================
# Clean target: remove binaries and object files
# ================================================
clean:
	rm -f $(OBJS) $(TARGET)
