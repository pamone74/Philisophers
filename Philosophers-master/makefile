# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pamone <pamone@student.42abudhabi.ae>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/03/22 12:24:59 by pamone            #+#    #+#              #
#    Updated: 2024/03/22 12:25:04 by pamone           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

CFLAGS = -Wall -Wextra -Werror -pthread

RM = rm -rf

SRCS = 	./src/main.c ./src/init.c ./src/libft.c ./src/philo.c ./src/utils.c ./src/table_actions.c 

$(NAME) :
	cc $(CFLAGS) $(SRCS) -o $(NAME)

all : $(NAME)

clean :
	$(RM) $(NAME)
	$(RM) ./src/.o

fclean : clean
	$(RM) $(NAME)
	
re : fclean all

.PHONY: all clean fclean re