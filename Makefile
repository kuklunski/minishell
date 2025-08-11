# Program name
NAME = minishell

# Compiler and flags
CC = cc
CFLAGS = -Wall -Wextra -Werror -g3
LDFLAGS = -lreadline

# Directories
SRCDIR = .
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
            libft/join_back.c

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

# All source files
SRC = $(MAIN_SRC) globals.c $(COMMANDS_SRC) $(ERRORS_SRC) $(EXPANSION_SRC) $(LIBFT_SRC) \
      $(MEMORY_SRC) $(PARSING_SRC) $(TOKENIZATION_SRC)

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

# Format all C and header files with 42 formatter
format:
	@echo "$(BLUE)Formatting code with 42 formatter...$(NC)"
	@find . -name "*.c" -o -name "*.h" | grep -v libft | xargs c_formatter_42
	@echo "$(GREEN)✓ Code formatted!$(NC)"

# Run norminette on all files
norm:
	@echo "$(BLUE)Running norminette...$(NC)"
	@norminette $(SRC) $(INCDIR)/

# Debug build with more verbose output
debug: CFLAGS += -DDEBUG -fsanitize=address
debug: $(NAME)
	@echo "$(GREEN)✓ Debug build completed!$(NC)"

# Help target
help:
	@echo "$(BLUE)Available targets:$(NC)"
	@echo "  $(GREEN)all$(NC)     - Build the project"
	@echo "  $(GREEN)clean$(NC)   - Remove object files"
	@echo "  $(GREEN)fclean$(NC)  - Remove object files and executable"
	@echo "  $(GREEN)re$(NC)      - Rebuild the project"
	@echo "  $(GREEN)format$(NC)  - Format code with 42 formatter"
	@echo "  $(GREEN)norm$(NC)    - Run norminette checker"
	@echo "  $(GREEN)debug$(NC)   - Build with debug flags"
	@echo "  $(GREEN)help$(NC)    - Show this help"

.PHONY: all clean fclean re format norm debug help
