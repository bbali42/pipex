# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bbali <bbali@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/12/19 13:06:27 by bbali             #+#    #+#              #
#    Updated: 2022/05/24 07:57:05 by bbali            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	pipex
CC			= 	gcc
CFLAGS		= 	-Wall -Werror -Wextra

SRC			= 	pipex.c utils.c path_format.c
OBJ			= 	$(SRC:.c=.o)

BONUS		=	bonus.c utils.c path_format.c
OBJB		= 	$(BONUS:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ)

%.o:%.c
		$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(OBJB)

fclean: clean
	rm -f $(NAME)

re: fclean all

bonus: $(OBJB)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJB)

.PHONY: clean fclean re