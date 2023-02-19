NAME = minitalk

SRCS = server.c client.c

RED=\033[0;31;41m
GREEN=\033[0;32m
YEL=\033[0;37;47m
CYA=\033[1;36m
RESET=\033[0m

LIB_DIR = libft/
LIB = $(LIB_DIR)/libft.a

CC = gcc
CFLAGS = -g -Wall -Werror -Wextra

OBJS = $(SRCS:.c=.o)

DEL = rm -rf

%o: %c 
	# @echo "$(RED).....................$(YEL).....................$(RESET)\n"
	@printf "$(GREEN)"
	@$(CC) $(CFLAG) -c $< -o $@ 

all: $(NAME)

$(NAME): $(OBJS)
	@make -C $(LIB_DIR)
	@$(CC) $(CFLAGS) $(LIB) -o $(NAME) $(OBJS)

clean:
	@make -C $(LIB_DIR) clean
	@$(DEL) $(OBJS)

fclean: clean
	# @say -v Kyoko "ちょっと待って、掃除中"
	@make -C $(LIB_DIR) fclean
	@$(DEL) $(NAME)
	# @cat pic/
	# @say -v Kyoko "お待たせしました"

re: fclean all

norm:
	# @cat pic/
	# @say -v Kanya "ขอตรวจ"
	# @say -v Kyoko "norminetto"
	# @say -v Kanya "หน่อยนะ"
	@echo "---- NORMINETTE ----"
	@norminette -R CheckDefine *.h
	@norminette -R CheckForbiddenSourceHeader *.c
	# @say -v Kanya "ขอบคุณที่รอ"
	@echo "---- THANK YOU ^w^Y ----"

.PHONY: norm clean fclean mlxnaa all re