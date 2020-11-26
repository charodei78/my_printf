# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hheimerd <hheimerd@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/07/17 11:12:46 by hheimerd          #+#    #+#              #
#    Updated: 2020/07/17 12:45:59 by hheimerd         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

FLAGS 		= -Wall -Wextra -Werror -fpic -O2 
CC 			= clang
NAME 		= libftprintf.a
HEADER		= printf/ft_printf.h
LIB_DIR		= libft
LIB			= $(LIB_DIR)/libft.a
HEADER_OBJ	= $(HEADER:.h=.h.gch)
HEADER_SO	= $(HEADER:.h=.so)
SRC			= printf/check_flags.c printf/check_size.c printf/ft_printf.c \
				utils/parse_char.c utils/parse_hex.c utils/parse_int.c \
				utils/parse_string.c utils/parse_un_int.c utils/printf_utils.c
SRC_OBJ		= $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(LIB) $(SRC_OBJ) $(HEADER_OBJ) 
	ar rcs $(NAME) $(SRC_OBJ) $(HEADER_OBJ)
	ar rcs $(NAME) $(LIB)

$(HEADER_OBJ):$(HEADER)
	$(CC) $(FLAGS) -c $(HEADER) $<
	ar rcs $(NAME) $@

$(LIB):
	make -C $(LIB_DIR);
	cp $(LIB) $(NAME)

clean:
	rm -f *.o */*.o $(HEADER_OBJ)

fclean: clean
	rm -f $(NAME) $(HEADER_SO)
	make fclean -C $(LIB_DIR)

re: fclean all

so: $(SRC_OBJ) $(HEADER_OBJ) $(BONUS_OBJ)
	gcc -shared -o $(HEADER_SO) *.o

.c.o:
	$(CC) $(FLAGS) -c $< -o $@
	ar rcs $(NAME) $@
