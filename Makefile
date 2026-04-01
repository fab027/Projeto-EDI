CC      = gcc
CFLAGS  = -Wall -Wextra -pedantic -std=c99 -Iinclude
SRC_DIR = src
OBJ_DIR = obj
BIN     = captacao

SRCS = $(wildcard $(SRC_DIR)/*.c)
OBJS = $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

.PHONY: all clean

all: $(OBJ_DIR) $(BIN)

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(BIN): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJ_DIR) $(BIN)
