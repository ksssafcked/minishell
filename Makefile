# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lsaiti <lsaiti@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/12/14 13:31:37 by qudomino          #+#    #+#              #
#    Updated: 2025/01/03 17:08:18 by lsaiti           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
CC = cc
CFLAGS = -Wall -Wextra -Werror -g
DPRINTF_DIR = dprintf
DPRINTF = $(DPRINTF_DIR)/libftprintf.a
SRC = src/main.c src/signals.c parser/parser.c env/env.c utils/utils.c \
	  utils/get_next_line.c utils/get_next_line_utils.c execute/execute.c \
	  execute/execute_pipeline.c execute/heredoc.c parser/parser_pipeline.c env/built_in.c \
	  src/expand.c parser/parser_utils.c parser/redirections.c env/built_in_cmd2.c  \
	  env/built_in_cmd.c env/handle_builtin.c env/builtin_var.c env/print_builtin.c \
	  env/builtin_checker.c env/builtin_free.c env/env_utils.c \
	  parser/parser_command.c parser/parser_redirect.c parser/parser_token_utils.c \
	  env/builtin_utils.c execute/execute_directory.c execute/execute_utils.c \
	  execute/heredoc_utils.c parser/parser_char.c parser/parser_process.c \
	  parser/parser_quotes.c parser/parser_token.c \
	  execute/execute_redirect.c execute/execute_redirect_utils.c execute/execute_child.c \
	  execute/execute_pipes.c execute/execute_pipeline_utils.c execute/execute_env.c \
	  utils/ft_alloc.c utils/ft_func.c utils/ft_func2.c utils/ft_split.c utils/ft_string_utils.c \
	  utils/ft_string.c src/free_content.c src/process.c src/read.c src/token.c src/token_utils.c \
	  src/fds.c src/handle.c src/shell.c src/main_utils.c parser/parser_quote_utils.c \
	  parser/parser_process_utils.c parser/parser_redirect_utils.c parser/parser_pp_utils.c \
	  env/print_utils.c execute/heredoc_process.c src/expand_utils.c src/expand_var.c src/expand_handle.c \
	  env/cd_builtin.c env/cd_parser.c src/process_utils.c execute/heredoc_2.c
 
OBJS = $(SRC:.c=.o)

all: $(DPRINTF) $(NAME)

$(DPRINTF):
	make -C $(DPRINTF_DIR)

$(NAME): $(OBJS) $(DPRINTF)
	$(CC) $(CFLAGS) $(OBJS) $(DPRINTF) -lreadline -o $(NAME)

clean:
	rm -f $(OBJS)
	make -C $(DPRINTF_DIR) clean

fclean: clean
	rm -f $(NAME)
	make -C $(DPRINTF_DIR) fclean

re: fclean all

