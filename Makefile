CC = c++

CC_FLAGS = -Wall -Werror -Wextra -std=c++98 -fsanitize=address

NAME := ft_container
	
SRCS := $(shell find -type f -name "*.cpp" | cut -c3-)

OBJS := $(SRCS:.cpp=.o)

all : $(NAME)

$(NAME):	$(addprefix objs/, $(OBJS)) Makefile
			$(CC) $(CC_FLAGS) $(addprefix objs/, $(OBJS)) -o $(NAME) 
objs/%SRCS.o:		%.cpp  Makefile $(shell find . -type f -name "*.hpp")
				@mkdir -p objs objs/commands
					$(CC) $(CC_FLAGS) -c $< -o "$@"

clean :
		rm -rf objs

fclean : clean
		rm -f $(NAME)

re : fclean all

.PHONY : re clean fclean all .PHONY