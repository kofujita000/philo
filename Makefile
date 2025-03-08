# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kofujita <kofujita@student42.tokyo>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/07 18:28:46 by kofujita          #+#    #+#              #
#    Updated: 2025/03/08 15:10:39 by kofujita         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME     := philo
LIB_NAME := lib$(NAME).a

# Default flag
CFLAGS := -Werror -Wall -Wextra

# Debug flag
CFLAGS += -ggdb # -fsanitize=thread

# Include directory
INCLUDE_DIR := -I./libphilo \
			   -I./include

# Command
CC    := cc
RM    := rm -rf
CP    := cp -r
MKDIR := mkdir -p
AR    := ar rc
MAKE  := make

# Source files
SRCS := $(shell find libphilo -name "*.c" -type f | sort)
MAIN := main.c

# Object directory
OBJS_DIR := objs

# Create Object directory
$(shell find libphilo -type d -exec mkdir -p $(OBJS_DIR)/{} \;)

# Object files
OBJS_NO_MAIN := $(SRCS:%.c=$(OBJS_DIR)/%.o)
OBJS_MAIN    := $(MAIN:%.c=$(OBJS_DIR)/%.o)
OBJS         := $(OBJS_NO_MAIN) $(OBJS_MAIN)

.PHONY:
	all clean fclean re library

$(OBJS_DIR)/%.o: %.c
	@$(CC) $(CFLAGS) $(INCLUDE_DIR) -c $< -o $@

all: $(NAME)

library:
	$(AR) $(LIB_NAME) $(OBJS_NO_MAIN) $(LIBRARIES)

$(NAME): $(OBJS) library
	$(MAKE) -C ./include/ft_std
	$(CC) $(CFLAGS) $(INCLUDE_DIR) -o $(NAME) $(OBJS_MAIN) $(LIB_NAME) ./include/ft_std/libftstd.a

clean:
	$(RM) $(OBJS_DIR)

fclean: clean
	$(RM) $(LIB_NAME)
	$(RM) $(NAME)

setup:
	$(shell find libphilo -type d -exec mkdir -p $(OBJS_DIR)/{} \;)

re: fclean setup all
