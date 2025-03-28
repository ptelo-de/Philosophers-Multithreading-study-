NAME			=	philo

CC				=	cc

CFLAGS			=	-Wall -Wextra -Werror -gdwarf-4

RM				=	rm -rf

INC_DIR			=	includes/

SRC_DIR			=	src/

OBJ_DIR			=	objs/

SRC				=	$(addprefix $(SRC_DIR), main.c inits.c, utils.c, check_args.c, frees.c, create_philos.c)

OBJ				=	$(SRC:$(SRC_DIR)%.c=$(OBJ_DIR)%.o)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $^ -o $@ -I $(INC_DIR) 

$(OBJ_DIR)%.o: $(SRC_DIR)%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@ -I $(INC_DIR)

$(OBJ_DIR):
	mkdir -p $@

all: $(NAME)

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