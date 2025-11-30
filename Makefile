# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rafasant <rafasant@student.42lisboa.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/08/29 19:44:47 by rafasant          #+#    #+#              #
#    Updated: 2025/11/30 18:01:45 by rafasant         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC 			= cc
CFLAGS		= -Wall -Wextra -Werror -g -O3
NAME 		= cub3D
RM			= rm -rf
HEADERS 	= $(addprefix -I, . catch_lib minilibx libft)
INCLUDE 	= catch_lib/catch.a minilibx/libmlx.a libft/libft.a
LINKS		= -lXext -lXfixes -lX11 -lm -lz
SRCS 		= $(addprefix ${SRCS_DIR}, cub3d.c parse_file.c parse_file_utils.c \
			parse_textures.c parse_colours.c static_structs.c window.c \
			map_parse.c hooks.c mouse.c mouse_utils.c clear.c map_border.c\
			xpms.c pixel_management.c images.c image_manipulation.c \
			screens.c resolution.c resolution_helpers.c raycaster.c \
			render.c full_map.c minimap.c clear_textures.c cells.c  \
			fire_sprite.c hose.c prepare_resources.c frame_managment.c\
			raycast_utils.c raycaster_2.c map_parse_utils.c map_parse_2.c \
			fire_sprite_utils.c static_structs_2.c init_visuals.c movement.c)
OBJS		= ${SRCS:${SRCS_DIR}%.c=${OBJS_DIR}%.o}
SRCS_DIR	= srcs/
OBJS_DIR	= objs/

${OBJS_DIR}%.o: ${SRCS_DIR}%.c
	@mkdir -p objs
	@${CC} ${CFLAGS} ${HEADERS} -c $< -o $@

all: ${INCLUDE} ${NAME}
${INCLUDE} :
	@echo "Compiling packages..."
	@make -C catch_lib --silent
	@make -C libft --silent
	@make -C minilibx --silent --no-print-directory > /dev/null 2>&1
	@echo "Packages compiled!"
${NAME} : ${OBJS}
	@${CC} ${CFLAGS} ${OBJS} ${INCLUDE} ${LINKS} -o ${NAME}
	@echo "Compiled $(NAME)."

clean: 
	@${RM} ${OBJS_DIR}
	@make clean -C catch_lib --silent
	@make clean -C libft --silent
	@make clean -C minilibx --silent > /dev/null 2>&1
	@echo "Cleaned object files!"

fclean: clean
	@${RM} ${NAME}
	@make fclean -C catch_lib --silent
	@make fclean -C libft --silent
	@echo "Cleaned executables!"

re: fclean all

.PHONY: clean, fclean, all, re
