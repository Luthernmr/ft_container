CC = c++

CC_FLAGS = -Wall -Werror -Wextra -std=c++98 #-fsanitize=address

NAME := ft_container
	
SRCS := $(shell find -type f -name "*.cpp") # | rev | cut -d '/' -f 1 | rev

HPPFILES = $(shell find -type f -name "*.hpp")


OBJS := $(SRCS:.cpp=.o)


all : $(NAME)

$(NAME) : 	%.cpp  Makefile $(CPPFILES)
			@mkdir -p objs
			$(CC) $(CC_FLAGS) -c $< -o $(NAME)


objs%.o:	%.cpp  Makefile $(HPPFILES)
			@mkdir -p objs
			$(CC) $(CC_FLAGS) -c $< -o $(NAME)

clean :
		rm -rf objs

fclean : clean
		rm -f $(NAME)

re : fclean all

test : $(shell bash test.sh)

.PHONY : re clean fclean all .PHONY