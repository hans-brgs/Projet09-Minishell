# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hbourgeo <hbourgeo@student.19.be>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/09/30 19:37:13 by hbourgeo          #+#    #+#              #
#    Updated: 2022/04/21 11:31:03 by hbourgeo         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

# Get DIR
INC_DIR = includes/
SRC_DIR = src/
OBJ_DIR = obj_$(basename $(NAME))/

# Edit FLAGS
CC = gcc 
CFLAGS = -Wall -Werror -Wextra -I $(INC_DIR)
DEPS = $(shell find $(INC_DIR) -type f -name "*.h")

# Get .c and convert to .o
SRCS = $(notdir $(shell find $(SRC_DIR) -type f -name "*.c"))
OBJS = $(addprefix $(OBJ_DIR), $(SRCS:.c=.o))

# Add search path
VPATH = $(INC_DIR) $(OBJ_DIR) $(shell find $(SRC_DIR) -type d)

# make rules
all : $(NAME)

$(OBJ_DIR)%.o : %.c $(DEPS)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR) :
	@mkdir -p $(OBJ_DIR)

$(NAME) : $(OBJ_DIR) $(OBJS)
	@ar -rcs $(NAME) $(OBJS)

clean :
	rm -rf $(OBJS)
	rm -rf $(OBJ_DIR)

fclean : clean
	rm -rf $(NAME)

re : fclean all

.PHONY : clean fclean all re

print-%: ; @echo $* = $($*)

# GIT

MSG = "default"
 
git: 
	@-git add .
	@git commit -am "`date +'%Y-%m-%d %H:%M:%S'` | $(MSG)"
	@-git push