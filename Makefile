# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: loris <loris@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/22 15:57:47 by loris             #+#    #+#              #
#    Updated: 2022/04/13 18:50:33 by loris            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minitalk.a

SRCS = client.c server.c

OBJS = $(SRCS:.c=.o)

CC				= gcc
RM				= rm -f
CFLAGS			= -Wall -Wextra -Werror -I.
RUN				= ar rcs

%.o: %.c
	$(CC) -c $(CFLAGS) -I headers $< -o $(<:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(MAKE) -C ./libft
	cp libft/libft.a $(NAME)


	$(CC) $(CFLAGS) server.o $(NAME) -fsanitize=address -o server
	$(CC) $(CFLAGS) client.o $(NAME) -fsanitize=address -o client


clean:
	$(MAKE) clean -C ./libft
	$(RM) $(NAME) $(OBJS)

fclean:
	$(MAKE) fclean -C ./libft
	$(RM) $(NAME) $(OBJS)

re: fclean all

.PHONY: all clean fclean re