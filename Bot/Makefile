NAME = robometeo

CC = c++

FLAGS = -g -Wall -Werror -Wextra -fPIE -std=c++98

SRCS =	main.cpp			\
		Bot.cpp
	

OBJS = $(SRCS:.cpp=.o)

%.o : %.cpp
	$(CC) $(FLAGS) -c -o $@ $<

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(FLAGS) $(OBJS) -o $(NAME) && mv $(NAME) ../

clean:
	rm -f $(OBJS) ../robometeo
	
fclean: clean
	rm -f $(NAME) ../robometeo

re: fclean all
	
.PHONY: all clean fclean re