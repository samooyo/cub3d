# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sadarnau <sadarnau@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/11/24 15:47:17 by sadarnau          #+#    #+#              #
#    Updated: 2020/01/11 19:49:04 by sadarnau         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3d

SRC_PATH = srcs
SRC_NAME = main.c parser.c get_next_line.c pixel.c utils.c \
			hook.c textures.c ray.c draw.c floor.c sprite.c error.c \
			parserbis.c parse_map.c bmp.c
OBJ_PATH = objs
OBJ_NAME = $(SRC_NAME:.c=.o)

CC = gcc -Werror -Wall -Wextra

CPPFLAGS = -I includes -I /usr/X11/include

LDFLAGS = -L 
LDLIBS = /usr/local/lib -lmlx -framework OpenGL -framework AppKit

SRC = $(addprefix $(SRC_PATH)/,$(SRC_NAME))
OBJ = $(addprefix $(OBJ_PATH)/,$(OBJ_NAME))

all: $(NAME)

$(NAME): $(OBJ)
	@$(CC) $(LDFLAGS) $(LDLIBS) $^ -o $@
	@echo "Je nous prepare quelque chose: \033[1;32mC'est fait !\033[m"

$(OBJ_PATH)/%.o: $(SRC_PATH)/%.c
	@mkdir $(OBJ_PATH) 2> /dev/null || true
	@$(CC) $(CFLAGS) -c $< $(CPPFLAGS) -o $@

clean:
	@rm -f $(OBJ)
	@rm -rf $(OBJ_PATH)
	@echo "J'efface presque tout </3"

fclean:
	@rm -f $(OBJ)
	@rm -rf $(OBJ_PATH)
	@rm -f $(NAME)
	@echo "J'efface notre jeu </3"

re: fclean all

.PHONY: all clean fclean re libft
