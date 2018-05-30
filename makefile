# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dhorvill <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/05/07 16:12:44 by dhorvill          #+#    #+#              #
#    Updated: 2018/05/29 07:47:30 by dhorvill         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = RTv1

LIBFT = libft.a

SRCS = rTv1.c interactive.c

OBJ = $(SRC=.c:.o)

INCLUDEPATH = libft/

CC = gcc

CFLAGS = -Wall -Werror -Wextra

all: $(NAME)

$(NAME): $(LIBFT) $(SRCS)
	@$(CC) $(CFLAGS) -I$(INCLUDEPATH) $(INCLUDEPATH)$(LIBFT) $(SRCS) -o $(NAME) -lmlx -framework OpenGL -framework AppKit

$(LIBFT):
	@cd libft && make

clean:
	@cd libft && make clean

fclean:
	@cd libft && make fclean
	@rm -f $(NAME)

re: fclean all
