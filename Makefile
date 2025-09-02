# Compiler and tools
CC      = gcc
NASM    = nasm
LD      = ld

# Flags
CFLAGS  = -fno-stack-protector -g3
NASMFLAGS = -f elf64
LDFLAGS = -e _start

# Directories
SRC_DIR = src
BUILD_DIR = build
INCLUDE_DIR = include
LIB_DIR = libc

# Files
ASM_SRC = crt0.asm
C_SRC = $(SRC_DIR)/main.c
LIB_SRC = $(SRC_DIR)/$(LIB_DIR)/libc.c

ASM_OBJ = $(BUILD_DIR)/$(ASM_SRC:.asm=.o)
C_OBJ = $(BUILD_DIR)/$(C_SRC:.c=.o)
LIB_OBJ = $(BUILD_DIR)/$(LIB_SRC:.c=.o)

TARGET = 0x41sh

# Default target
all: $(TARGET)

# Link all objects
$(TARGET): $(ASM_OBJ) $(C_OBJ) $(LIB_OBJ)
	$(LD) $(LDFLAGS) -o $@ $^

# Compile ASM
$(ASM_OBJ): $(ASM_SRC)
	$(NASM) $(NASMFLAGS) $< -o $@

# Compile C sources
$(C_OBJ) : $(C_SRC)
	$(CC) $(CFLAGS) -o $@ -c $< -I $(INCLUDE_DIR)

$(LIB_OBJ) : $(LIB_SRC)
	$(CC) $(CFLAGS) -o $@ -c $< -I $(INCLUDE_DIR)

# Clean object files
clean:
	rm -f $(BUILD_DIR)/*.o
	rm -f $(BUILD_DIR)/$(SRC_DIR)/*.o
	rm -f $(BUILD_DIR)/$(SRC_DIR)/$(LIB_DIR)/*.o

# Clean everything
fclean: clean
	rm -f $(TARGET)

# Rebuild everything
re: fclean all

.PHONY: all clean fclean re
