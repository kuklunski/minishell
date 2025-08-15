# Program name
NAME = minishell

# Compiler and flags
CC = cc
CFLAGS = -Wall -Wextra -Werror
LDFLAGS = -lreadline

# Directories
OBJDIR = obj
INCDIR = includes

# Source files
MAIN_SRC = main.c

COMMANDS_SRC = commands/cmd_list_append.c \
               commands/commands.c \
               commands/commands_with_no_args.c \
               commands/handle_append.c \
               commands/handle_heredoc.c \
               commands/handle_heredoc1.c \
               commands/handle_heredoc2.c \
               commands/handle_input_redirection.c \
               commands/handle_pipe.c \
               commands/handle_trunc_redirection.c \
               commands/handle_word.c \
               commands/handle_word1.c \
               commands/handle_word2.c \
               commands/handle_word3.c \
               commands/handle_word4.c \
               commands/handle_word5.c \
               commands/handle_word6.c

ERRORS_SRC = errors/error_msg.c

EXPANSION_SRC = expansion/expand_var.c \
                expansion/expand_var_heredoc.c \
                expansion/expand_var_utils.c \
                expansion/expand_var_utils1.c \
                expansion/expand_var_utils2.c \
                expansion/expansion.c \
                expansion/expansion_heredoc.c \
                expansion/expansion_utils.c \
                expansion/expansion_utils1.c \
                expansion/expansion_utils2.c \
                expansion/expansion_utils3.c

LIBFT_SRC = libft/ft_calloc.c \
            libft/ft_itoa.c \
            libft/ft_memset.c \
            libft/ft_putendl_fd.c \
            libft/ft_split.c \
            libft/ft_strchr.c \
            libft/ft_strcmp.c \
            libft/ft_strdup.c \
            libft/ft_strjoin.c \
            libft/ft_strlen.c \
            libft/ft_strncmp.c \
            libft/ft_substr.c \
            libft/join_back.c \
            libft/ft_isdigit.c \
            libft/ft_isalpha.c \
            libft/ft_isalnum.c \
            libft/ft_isspace.c \
            libft/ft_putstr_fd.c

MEMORY_SRC = memory/frees.c \
             memory/frees1.c \
             memory/init_inf_outf.c \
             memory/init_data.c \
             memory/init_utils.c \
             memory/init_working_dirs.c

PARSING_SRC = parsing/parser.c \
              parsing/quotes.c \
              parsing/quotes1.c \
              parsing/quotes2.c \
              parsing/var_or_consecutive.c \
              parsing/var_or_consecutive_utils.c

TOKENIZATION_SRC = tokenization/add_token_to_list.c \
                   tokenization/create_token.c \
                   tokenization/delete_token.c \
                   tokenization/first_checks.c \
                   tokenization/process_type.c \
                   tokenization/token_separator.c \
                   tokenization/token_word.c \
                   tokenization/tokenizer.c \
                   tokenization/utils.c

BUILTINS_SRC =    builtins/cd_builtin.c \
                  builtins/echo_builtin.c \
                  builtins/env_builtin.c \
                  builtins/exit_builtin.c \
                  builtins/export_unset_builtin.c \
                  builtins/pwd_builtin.c \

ENV_SRC = env/env_set.c env/env.c

EXECUTION_SRC = execution/execute_cmd.c \
                  execution/execute_utils.c \
                  execution/execute.c \
                  execution/parse_path.c

REDIRECTIONS_SRC = redirections/file_io.c \
                  redirections/pipe.c

SIGNALS_SRC = signals/signal.c

UTILS_SRC = utils/cleanup.c \
            utils/error.c

# All source files
SRC = $(MAIN_SRC) $(COMMANDS_SRC) $(ERRORS_SRC) $(EXPANSION_SRC) $(LIBFT_SRC) \
      $(MEMORY_SRC) $(PARSING_SRC) $(TOKENIZATION_SRC) $(SIGNALS_SRC) $(UTILS_SRC) \
      $(REDIRECTIONS_SRC) $(EXECUTION_SRC) $(ENV_SRC) $(BUILTINS_SRC)

# Object files
OBJ = $(SRC:%.c=$(OBJDIR)/%.o)

# Include flags
INCLUDES = -I$(INCDIR)

# Colors for output
RED = \033[0;31m
GREEN = \033[0;32m
YELLOW = \033[0;33m
BLUE = \033[0;34m
NC = \033[0m # No Color

# Rules
all: $(NAME)

$(NAME): $(OBJ)
	@echo "$(BLUE)Linking $(NAME)...$(NC)"
	@$(CC) $(OBJ) $(LDFLAGS) -o $(NAME)
	@echo "$(GREEN)✓ $(NAME) compiled successfully!$(NC)" 

$(OBJDIR)/%.o: %.c
	@mkdir -p $(dir $@)
	@echo "$(YELLOW)Compiling $<...$(NC)"
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	@echo "$(RED)Cleaning object files...$(NC)"
	@rm -rf $(OBJDIR)
	@echo "$(GREEN)✓ Object files cleaned!$(NC)"

fclean: clean
	@echo "$(RED)Cleaning $(NAME)...$(NC)"
	@rm -f $(NAME)
	@echo "$(GREEN)✓ $(NAME) cleaned!$(NC)"

re: fclean all

.PHONY: all clean fclean re format norm debug help
