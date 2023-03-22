# ---------------------------------------------------------------------------- #
#                                   Makefile                                   #
# ---------------------------------------------------------------------------- #

NAME 			=	ft_container

CC 				=	c++
CC_FLAGS 		=	-Wall -Werror -Wextra -std=c++98 -fsanitize=address

SRCS 			=	main.cpp
OBJS 			=	$(SRCS:.cpp=.o)

OBJS_PREFIX		=	$(addprefix $(OBJS_DIR), $(OBJS))

HEADERS			=	$(shell find -type f -name "*.hpp")

OBJS_DIR		=	objs/
TRACES_DIR		= 	traces/ \
					traces/diff\
					traces/time\

all: $(NAME)

$(OBJS_DIR)%.o:		%.cpp $(HEADERS) Makefile
					@mkdir -p $(OBJS_DIR)
					$(CC) $(CC_FLAGS) -c $< -o $@
					@printf "\033[2K\r\033[0;96m[BUILD]\033[0m $(NAME)\n"

$(NAME):			$(OBJS_PREFIX)
					$(CC) $(CC_FLAGS) -o $(NAME) $(OBJS_PREFIX)
					@printf "\033[2K\r\033[0;96m[END]\033[0m $(NAME)\n"
					@printf "\n"

clean:
	rm -rf $(OBJS_DIR)
	rm -rf $(TRACES_DIR)
	@printf "\033[2K\r\033[0;96m[CLEAN]\033[0m done\n"

fclean: clean
	rm -f $(NAME)
	@printf "\033[2K\r\033[0;96m[FCLEAN]\033[0m done\n"

re: fclean all

diff:
	mkdir -p $(TRACES_DIR)
	@bash diff.sh

.PHONY: all clean fclean re diff