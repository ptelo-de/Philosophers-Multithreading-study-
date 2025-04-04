NAME			=	philo

CC				=	cc

CFLAGS			=	-Wall -Wextra -Werror -g

RM				=	rm -rf

INC_DIR			=	include/

SRC_DIR			=	src/

OBJ_DIR			=	objs

SRCS = $(shell find $(SRC_DIR) -type f -name "*.c")
OBJS = $(patsubst $(SRC_DIR)%.c, $(OBJ_DIR)/%.o, $(SRCS))
#SRC				=	$(addprefix $(SRC_DIR), utils.c, inits.c, check_args.c, frees.c, create_philos.c, main.c)

#OBJ				=	$(SRC:$(SRC_DIR)%.c=$(OBJ_DIR)%.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $^ -o $@ -I $(INC_DIR) 

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@echo "$(YELLOW)Compiling $<...$(RESET)"
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(IFLAGS) -c $< -o $@
#$(OBJ_DIR)%.o: $(SRC_DIR)%.c | $(OBJ_DIR)
#	$(CC) $(CFLAGS) -c $< -o $@ -I $(INC_DIR)

#$(OBJ_DIR):
#	mkdir -p $@


clean:
	$(RM) $(OBJ_DIR)

fclean: clean
	$(RM) $(NAME)

re: fclean all

val: $(NAME)
	clear
	valgrind --leak-check=full ./$(NAME) $(INPUT)

hel: $(NAME)
	clear
	valgrind --tool=helgrind ./$(NAME) $(INPUT)

drd: $(NAME)
	clear
	valgrind --tool=drd ./$(NAME) $(INPUT)