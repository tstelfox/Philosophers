# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: tmullan <tmullan@student.codam.nl>           +#+                      #
#                                                    +#+                       #
#    Created: 2021/05/27 13:10:33 by tmullan       #+#    #+#                  #
#    Updated: 2021/06/24 21:38:45 by tmullan       ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME = plate_o

INCLUDES = -Iincludes

UTILS = utils/ft_putstr_fd.o \
		utils/ft_strlen.o \
		utils/ft_atoi.o \
		utils/ft_bzero.o

OBJ = main.o \
		$(UTILS)

FLAGS = -Wall -Wextra -Werror

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(FLAGS) $(OBJ) $(INCLUDES) -o $(NAME) -fsanitize=thread

%.o: %.c
	@$(CC) $(FLAGS) $(INCLUDES) -pthread -c $< -o $@ -fsanitize=thread

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all
