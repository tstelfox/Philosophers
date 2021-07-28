# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: tmullan <tmullan@student.codam.nl>           +#+                      #
#                                                    +#+                       #
#    Created: 2021/05/27 13:10:33 by tmullan       #+#    #+#                  #
#    Updated: 2021/07/28 15:44:29 by tmullan       ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME = philo

INCLUDES = -Iincludes

UTILS = utils/ft_putstr_fd.o \
		utils/ft_strlen.o \
		utils/ft_atoi.o \
		utils/ft_bzero.o \
		utils/ft_isdigit.o

OBJ = main.o \
		threads.o \
		eat_loop.o \
		print_action.o \
		time_func.o \
		free_all.o \
		initialise.o \
		$(UTILS)

FLAGS = -Wall -Wextra -Werror

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(FLAGS) $(OBJ) $(INCLUDES) -o $(NAME) 

%.o: %.c
	@$(CC) $(FLAGS) $(INCLUDES) -pthread -c $< -o $@ 

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all
