NAME			=	philo

CC				=	cc

CFLAGS			=	-fsanitize=thread -g -pthread #-Wall -Wextra -Werror 

RM				=	rm -rf

INC_DIR			=	include/

SRC_DIR			=	src/

OBJ_DIR			=	objs

SRCS = $(shell find $(SRC_DIR) -type f -name "*.c")
OBJS = $(patsubst $(SRC_DIR)%.c, $(OBJ_DIR)/%.o, $(SRCS))

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $^ -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(INC_DIR)
	@echo "$(YELLOW)Compiling $<...$(RESET)"
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJ_DIR)

fclean: clean
	$(RM) $(NAME)

re: fclean all
