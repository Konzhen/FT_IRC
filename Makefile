NAME = ircserv

CC = c++

FLAGS = -g -Wall -Wextra -Werror -std=c++98

SRCS =	main.cpp			\
	Channel.cpp				\
	Client.cpp				\
	Command.cpp				\
	Parser.cpp				\
	Server.cpp				\
	User.cpp				\
	Commands/Kick.cpp		\
	Commands/Mode.cpp		\
	Commands/Nick.cpp		\
	Commands/Notice.cpp		\
	Commands/Part.cpp		\
	Commands/Pass.cpp		\
	Commands/Quit.cpp		\
	Commands/PrivMsg.cpp	\
	Commands/Ping.cpp		\
	Commands/Pong.cpp		\
	Commands/Join.cpp		\
	

OBJS = $(SRCS:.cpp=.o)

%.o : %.cpp
	$(CC) $(FLAGS) -c -o $@ $<

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(FLAGS) $(OBJS) -o $(NAME)

clean:
	rm -f $(OBJS)
	
fclean: clean
	rm -f $(NAME)

re: fclean all
	
.PHONY: all clean fclean re bonus