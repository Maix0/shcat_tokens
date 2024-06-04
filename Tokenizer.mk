# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Tokenizer.mk                                       :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: maiboyer <maiboyer@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/28 17:28:30 by maiboyer          #+#    #+#              #
#    Updated: 2024/06/04 23:03:37 by maiboyer         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

ANAME = tok

# Functions
link_group = -Wl,--start-group $(1) -Wl,--end-group

# Variables

BUILD_DIR ?= ./build

# Flags
CFLAGS 	= -Werror -Wextra -Wall -Wno-unused-command-line-argument -g3 -MMD -I./include -I./output/include -I./stdme/output/include -rdynamic -Wl,-E
# CFLAGS += -fsanitize=address -fno-omit-frame-pointer -fsanitize-address-use-after-return=runtime -fno-common -fsanitize-address-use-after-scope
# Sources
# LIB =	./libft/ft_bzero.c \
# 		./libft/ft_calloc.c \
# 		./libft/ft_memset.c \
# 		./libft/ft_split.c \
# 		./libft/ft_strcmp.c \
# 		./libft/ft_strdup.c \
# 		./libft/ft_strlcpy.c \
# 		./libft/ft_strjoin.c \
# 		./libft/ft_strlen.c

SRC_DIR = src
GEN_DIR = output

SRC =	$(addprefix $(SRC_DIR)/,$(shell cat ./src.list)) $(addprefix $(GEN_DIR)/,$(shell cat ./gen.list))
# Name
NAME = tokenizer

# Commands
CC ?= clang
RM = rm -rf

# Objects
OBJ = $(addprefix $(BUILD_DIR)/$(ANAME)/,$(SRC:.c=.o))

# Colors
GREEN = \033[32m
GREY = \033[0;90m
RED = \033[0;31m
GOLD = \033[38;5;220m
END = \033[0m

.PHONY: all bonus

LIBS_NAMES = me aq
LIBS_FILES = $(addprefix $(BUILD_DIR)/, $(addsuffix .a, $(addprefix lib, $(LIBS_NAMES))))
LIBS_FLAGS = $(addprefix -l, $(LIBS_NAMES))

all:
	@$(MAKE) -C ./stdme/ "LIB_NAME=$(shell realpath ./stdme)/"							"BUILD_DIR=$(BUILD_DIR)" libme.a
	@$(MAKE) -C ./allocator/ "LIB_NAME=$(shell realpath ./allocator)/"					"BUILD_DIR=$(BUILD_DIR)" libaq.a
	@# @$(MAKE) -C ./ast/ "LIB_NAME=$(shell realpath ./ast)/"							"BUILD_DIR=$(BUILD_DIR)" libast.a
	@# @$(MAKE) -C ./parser/ -f./Grammar.mk "LIB_NAME=$(shell realpath ./parser)/" 		"BUILD_DIR=$(BUILD_DIR)" libgmr.a
	@$(MAKE) -f./Tokenizer.mk $(NAME)


bonus:
	@$(MAKE) -f./Tokenizer.mk all

# Dependences for all
$(NAME): $(OBJ) $(LIBS_FILES)
	@echo -e '$(GREY) Linking\t$(END)$(GREEN)$(NAME)$(END)'
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJ) -L$(BUILD_DIR) $(call link_group,$(LIBS_FLAGS))

# Creating the objects
$(BUILD_DIR)/$(ANAME)/%.o: %.c
	@mkdir -p $(dir $@)
	@echo -e '$(GREY) Compiling\t$(END)$(GREEN)$<$(END)'
	@$(CC) $(CFLAGS) -o $@ -c $<

-include	${OBJ:.o=.d}
