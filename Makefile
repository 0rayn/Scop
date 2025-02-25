NAME = scop

CC = gcc
CFLAGS = -Wextra -Werror -Wall -Iinclude
LFLAGS = -lglfw -lvulkan

SRC_DIR = src
BUILD_DIR = build

SRC = $(shell find $(SRC_DIR) -type f -name "*.c")
OBJ = $(patsubst $(SRC_DIR)/%.c, $(BUILD_DIR)/%.o, $(SRC))

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME) $(LFLAGS)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD_DIR):
	@mkdir -p $(BUILD_DIR)

run: all
	@./scop

clean:
	rm -rf $(BUILD_DIR)
fclean: clean	
	rm -rf $(NAME)

re: clean all

.PHONY: re clean fclean all
