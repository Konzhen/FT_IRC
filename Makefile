NAME = ircserv

CC = c++

FLAGS = -g -Wall -Werror -Wextra -fPIE -std=c++98

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
	Commands/Meteo.cpp		\
	Commands/Invite.cpp		\
	Commands/Topic.cpp		\
	
OBJS = $(SRCS:.cpp=.o)

%.o : %.cpp
	$(CC) $(FLAGS) -c -o $@ $<

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(FLAGS) $(OBJS) -o $(NAME)

clean:
	rm -f $(OBJS) weather.json
	make clean -C Bot/
	
fclean: clean
	rm -f $(NAME) weather.json
	make fclean -C Bot/


re: fclean all

bonus: all
	make -C Bot/
	
.PHONY: all clean fclean re bonus
