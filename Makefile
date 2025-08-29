# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rafasant <rafasant@student.42lisboa.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/08/29 19:44:47 by rafasant          #+#    #+#              #
#    Updated: 2025/08/29 20:03:36 by rafasant         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC 			= cc
CFLAGS		= -Wall -Wextra -Werror ${HEADERS}
NAME 		= cub3D
RM			= rm -rf
HEADERS 	= $(addprefix -I, . catch_lib)
INCLUDE 	= catch_lib/catch.a
SRCS 		= $(addprefix ${SRCS_DIR} )
OBJS		= ${SRCS:${SRCS_DIR}%.c=${OBJS_DIR}%.o}
SRCS_DIR	= srcs/
OBJS_DIR	= objs/

${OBJS_DIR}%.o: ${SRCS_DIR}%.c
	@mkdir -p objs
	@${CC} ${CFLAGS} -c $< -o $@

all: ${INCLUDE} ${NAME}
${INCLUDE} :
	@echo "Compiling catch_lib..."
	@make -C catch_lib --silent
	@make clean -C catch_lib --silent
	@echo "Catch_lib compiled!"
${NAME} : ${OBJS}
	@${CC} ${CFLAGS} ${OBJS} ${INCLUDE} -o ${NAME}
	@echo "Compiled $(NAME)."

clean: 
	@${RM} ${OBJS_DIR}
	@echo "Cleaned object files!"

fclean: clean
	@${RM} ${NAME}
	@make fclean -C catch_lib --silent
	@echo "Cleaned executables!"

re: fclean all

.PHONY: clean, fclean, all, re