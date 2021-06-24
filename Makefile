# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: tmullan <tmullan@student.codam.nl>           +#+                      #
#                                                    +#+                       #
#    Created: 2021/05/27 13:10:33 by tmullan       #+#    #+#                  #
#    Updated: 2021/06/24 18:38:00 by tmullan       ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME = plate_o

INCLUDES = -Iincludes

UTILS = utils/ft_putstr_fd.o \
		utils/ft_strlen.o \
		utils/ft_atoi.o

OBJ = main.o \
		$(UTILS)

FLAGS = -Wall -Wextra -Werror

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(FLAGS) $(OBJ) $(INCLUDES) -o $(NAME)
	 # -fsanitize=thread

%.o: %.c
	@$(CC) $(FLAGS) $(INCLUDES) -pthread -c $< -o $@ 

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all
