NAME = server client

SRCS = server.c client.c

RED=\033[0;31;41m
GREEN=\033[0;32m
YEL=\033[0;37;47m
CYA=\033[1;36m
RESET=\033[0m

CC = gcc
CFLAGS = -g -Wall -Werror -Wextra

OBJS = $(SRCS:.c=.o)

DEL = rm -rf

%o: %c 
	@printf "$(CYA)"
	@$(CC) $(CFLAG) -c $< -o $@ 

all: $(NAME)

$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) server.o -o server
	@$(CC) $(CFLAGS) client.o -o client

clean:
	@$(DEL) $(OBJS)

fclean: clean
	@$(DEL) $(NAME)

re: fclean all

norm:
	@echo "---- NORMINETTE ----"
	@norminette -R CheckDefine *.h
	@norminette -R CheckForbiddenSourceHeader *.c
	@echo "---- THANK YOU ^w^Y ----"

.PHONY: norm clean fclean all re