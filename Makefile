# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ybouyzem <ybouyzem@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/07/13 22:26:51 by ybouyzem          #+#    #+#              #
#    Updated: 2024/10/17 12:27:03 by ybouyzem         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

READLINEDIR = $(shell brew --prefix readline)
LIB_FILES	:= libft/ft_isalpha.c libft/ft_isdigit.c libft/ft_isalnum.c libft/ft_strlen.c libft/ft_isspace.c\
	libft/ft_strlcpy.c libft/ft_strlcat.c libft/ft_strchr.c \
	libft/ft_atoi.c libft/ft_strdup.c \
	libft/ft_substr.c libft/ft_strjoin.c libft/ft_strtrim.c libft/ft_split.c libft/ft_itoa.c \
	libft/ft_putstr_fd.c 

FILE = src/main.c src/check_syntax.c src/parssing_utils.c src/split_args.c src/split_cmds.c src/list_utils.c src/expanding.c src/tty.c \
	src/expanding_utils1.c  src/expanding_utils2.c src/expanding_utils3.c src/expanding_utils4.c  src/expanding_utils5.c src/expanding_split.c src/add_spaces.c \
	src/expanding_ambiguous.c src/double_quotes.c src/double_quotes_utils.c src/single_quotes.c src/split_cmds_utils.c \
	exec/commands.c exec/builtins.c exec/envp_utils.c exec/envp_utils2.c exec/ft_split.c exec/str_utils.c exec/redrection.c exec/utils.c exec/main_exec.c \
	src/free_memory.c exec/piping.c exec/export.c exec/cd.c exec/exec_utils.c exec/signals.c exec/herdoc.c exec/utils2.c exec/expanding_herdoc.c \
	exec/herdoc_utils.c exec/echo.c exec/garbage_collect.c exec/error_handle.c $(LIB_FILES)

CFLAGS = -I $(READLINEDIR)/include
LDFLAGS = -L $(READLINEDIR)/lib -lreadline
HEADERS = includes/minishell.h includes/minishell_exec.h libft/libft.h
CC = cc
GFLAG = $(CC) -Wall -Wextra -Werror $(CFLAGS) 
OBJECTFILES = $(FILE:.c=.o)
PROGRAM = minishell

%.o: %.c $(HEADERS)
	$(GFLAG) -o $@ -c $<
 
$(PROGRAM): $(OBJECTFILES) $(HEADERS)
	$(CC) $(LDFLAGS) $(OBJECTFILES) -o $(PROGRAM)

all: $(PROGRAM)

clean:
	rm -f $(OBJECTFILES)

fclean: clean
	rm -f $(PROGRAM)

re: fclean all

.PHONY: clean