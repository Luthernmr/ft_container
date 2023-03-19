CC = c++
CC_FLAGS = -Wall -Werror -Wextra -std=c++98 #-fsanitize=address
NAME = ft_container
SRCS = main.cpp
OBJS = $(SRCS:.cpp=.o)
OBJS_DIR = objs/

OBJS_PREFIX = $(addprefix $(OBJS_DIR), $(OBJS))
HEADERS = $(shell find -type f -name "*.hpp")

TRACES_DIR	= 	traces/ \
				traces/diff\
				traces/time\

all: $(NAME)

$(OBJS_DIR)%.o: %.cpp $(HEADERS) Makefile
				@mkdir -p $(OBJS_DIR)
				$(CC) $(CC_FLAGS) -c $< -o $@
				@printf "\033[2K\r\033[0;32m[BUILD]\033[0m $(NAME)\n"

$(NAME): $(OBJS_PREFIX)
			$(CC) $(CC_FLAGS) -o $(NAME) $(OBJS_PREFIX)
			@printf "\033[2K\r\033[0;32m[END]\033[0m $(NAME)\n"

clean:
	rm -rf $(OBJS_DIR)
	rm -rf $(TRACES_DIR)
	@printf "\033[2K\r\033[0;32m[CLEAN]\033[0m done\n"

fclean: clean
	rm -f $(NAME)
	@printf "\033[2K\r\033[0;32m[FCLEAN]\033[0m done\n"

re: fclean all

time:
	mkdir -p $(TRACES_DIR)
	@bash timediff.sh

.PHONY: all clean fclean re time