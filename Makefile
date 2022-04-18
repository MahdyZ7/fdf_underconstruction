# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ayassin <ayassin@student.42abudhabi.ae>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/04/05 13:07:14 by ayassin           #+#    #+#              #
#    Updated: 2022/04/17 14:14:29 by ayassin          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fdf

HEADER = fdf.h

SRC = fdf.c readmap.c get_next_line.c key_hook.c draw_grid.c dummy_functions.c

SUBDIRS = libft_beta ft_printf_beta minilibx_macos

OBJDIR = fdf_objects

CC = gcc

CFLAGS = -Werror -Wall -Wextra

OBJS = $(SRC:.c=.o)

all: $(NAME)

.c.o:
	$(CC) $(CFLAGS) -Iminilibx_macos -Ilibft_beta -Ift_printf_beta -c $^ -o $@

$(NAME): $(SUBDIRS) $(OBJS)
	for dir in $(SUBDIRS); do \
        $(MAKE) all -C $$dir; \
    done
	$(CC) $(CFALGS) $(SRC) -Lminilibx_macos -lmlx -framework OpenGl -framework APPKit \
		-Llibft_beta -lft -Lft_printf_beta -lftprintf -o $(NAME)

$(SUBDIRS):
	for dir in $(SUBDIRS); do \
        $(MAKE) all -C $$dir; \
    done

clean:
	rm -f $(OBJS)
	for dir in $(SUBDIRS); do \
        $(MAKE) clean -C $$dir; \
    done

fclean: clean
	rm -f $(NAME)
	for dir in $(SUBDIRS); do \
        $(MAKE) fclean -C $$dir; \
    done

re : fclean all

.PHONY: clean fclean all re