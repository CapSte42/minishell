# Target name
NAME = minishell
# Compiler
CC = cc
# Compilation flags
FLAGS = -g -pedantic -Wall -Wextra -Werror -lreadline -Iinclude
# Library paths
LIBFT_PATH := ./libft
# Library files
LIBFT := $(LIBFT_PATH)/libft.a
# Debug flag
DBG ?= 0
# Source files
SRC = ./src/src_builtin/cd/find_in_env.c \
	./src/src_builtin/cd/ft_cd.c \
	./src/src_builtin/cd/my_getcwd.c \
	./src/src_builtin/cd/print_and_return.c \
	./src/src_builtin/echo/ft_echo.c \
	./src/src_builtin/env/env_related.c \
	./src/src_builtin/env/matrix_len.c \
	./src/src_builtin/exit/ft_exit.c \
	./src/src_builtin/exit/ft_strict_atoll.c \
	./src/src_builtin/exit/is_digit.c \
	./src/src_builtin/exit/set_exit_value.c \
	./src/src_builtin/expansion/check_quotes.c \
	./src/src_builtin/expansion/expand_and_copy.c \
	./src/src_builtin/expansion/expand_and_copy_utils.c \
	./src/src_builtin/expansion/quotes_count.c \
	./src/src_builtin/expansion/quotes_expansion.c \
	./src/src_builtin/expansion/var_allocate.c \
	./src/src_builtin/expansion/var_count.c \
	./src/src_builtin/expansion/var_expansion.c \
	./src/src_builtin/expansion/var_name_len.c \
	./src/src_builtin/expansion/var_value_len.c \
	./src/src_builtin/export/check_double.c \
	./src/src_builtin/export/check_in_env.c \
	./src/src_builtin/export/check_str.c \
	./src/src_builtin/export/copy_env.c \
	./src/src_builtin/export/export_utils.c \
	./src/src_builtin/export/find_value.c \
	./src/src_builtin/export/ft_export.c \
	./src/src_builtin/export/ft_print_export_menu.c \
	./src/src_builtin/export/ft_strcmp_env.c \
	./src/src_builtin/export/get_var_value.c \
	./src/src_builtin/export/value_sign.c \
	./src/src_builtin/export/var_name.c \
	./src/src_builtin/pwd/ft_pwd.c \
	./src/src_builtin/unset/biggest_str.c \
	./src/src_builtin/unset/ft_unset.c \
	./src/src_builtin/utils/utils.c \
	./src/src_builtin/wildcard/refactor.c \
	./src/src_builtin/wildcard/wildcard_check.c \
	./src/src_builtin/wildcard/wildcard_con_return.c \
	./src/src_builtin/wildcard/wildcard_utils.c \
	./src/src_environment/environment.c \
	./src/src_exec/exec_pipe.c \
	./src/src_exec/exec_tree.c \
	./src/src_exec/exec_utils.c \
	./src/src_exec/exec_utils2.c \
	./src/src_exec/execution.c \
	./src/src_exec/redirect.c \
	./src/src_exec/tree_algo.c \
	./src/src_exec/tree_utils.c \
	./src/src_lexer/ft_isand.c \
	./src/src_lexer/ft_isappend.c \
	./src/src_lexer/ft_iscmd.c \
	./src/src_lexer/ft_isdir.c \
	./src/src_lexer/ft_isfile.c \
	./src/src_lexer/ft_isheredoc.c \
	./src/src_lexer/ft_isor.c \
	./src/src_lexer/ft_isword.c \
	./src/src_lexer/lexer.c \
	./src/src_lexer/lexer_utils.c \
	./src/src_mainflow/create_redir_list.c \
	./src/src_mainflow/create_tree_array.c \
	./src/src_mainflow/here_doc.c \
	./src/src_mainflow/main_flow.c \
	./src/src_parser/balanced_utils.c \
	./src/src_parser/expand_str.c \
	./src/src_parser/ft_fix_args.c \
	./src/src_parser/grammar_check.c \
	./src/src_parser/operator_handling.c \
	./src/src_parser/parser.c \
	./src/src_parser/quote_handling.c \
	./src/src_parser/syntax_utils.c \
	./src/src_parser/token_merging.c \
	./src/src_process/process.c \
	./src/src_rl/balance.c \
	./src/src_rl/balance_check.c \
	./src/src_rl/input_handling.c \
	./src/src_rl/token_type.c \
	./src/src_rl/working_dir.c \
	./src/src_signal/setup_signal_handlers.c \
	./src/src_token/token_get.c \
	./src/src_token/token_handling.c \
	./src/src_token/token_handling_utils.c \
	./src/src_token/token_management.c


# Main target
$(NAME): $(LIBFT) $(SRC)
	if ! $(CC) $(SRC) $(FLAGS) $(LIBFT) -DDEBUG=$(DBG) -o $(NAME) 2>error.log; then \
		echo "${BOLD}${RED}Compilation failed${NO_COLOR}" | tee -a error.log; \
		echo "${BOLD}${RED}Error log created${NO_COLOR}"; \
		if  $(CC) $(SRC) -lreadline -Iinclude $(LIBFT) -o $(NAME) 2>/dev/null; then \
			echo "${BOLD}${GREEN}Compilation in easy mode successful${NO_COLOR}"; \
		else \
			echo "${BOLD}${RED}Compilation in easy mode failed${NO_COLOR}"; \
		fi \
	else \
		echo "${BOLD}${GREEN}Compilation successful${NO_COLOR}"; \
		rm -f error.log; \
	fi
# Build the LibFT library
$(LIBFT):
	make -C $(LIBFT_PATH)  all
# Build all target
all: $(NAME)
# Clean and rebuild target
re: fclean all
# Clean object files
clean:
	if [ -n "$$(find $(LIBFT_PATH) -name '*.o' -print -quit)" ]; then \
		make -C $(LIBFT_PATH) clean; \
		echo; \
		echo "${BOLD}${YELLOW}Cleaned object files${NO_COLOR}"; \
	fi
# Full clean
fclean: clean
	if [ -e $(LIBFT) ]; then \
		make -C $(LIBFT_PATH) fclean; \
		echo; \
		echo "${BOLD}${YELLOW}Removed  -> ${BLUE}libft.a${NO_COLOR}"; \
	fi
	if [ -e $(NAME) ]; then \
		rm -f $(NAME); \
		echo; \
		echo "${BOLD}${YELLOW}Removed  -> ${RED}$(NAME)${NO_COLOR}"; \
	fi

supp:
	touch ~/.supp.supp
	echo "{" > ~/.supp.supp
	echo "   IgnoreReadlineLeak" >> ~/.supp.supp
	echo "   Memcheck:Leak" >> ~/.supp.supp
	echo "   match-leak-kinds: reachable" >> ~/.supp.supp
	echo "   ..." >> ~/.supp.supp
	echo "   fun:add_history" >> ~/.supp.supp
	echo "   ..." >> ~/.supp.supp
	echo "}" >> ~/.supp.supp
	echo "{" >> ~/.supp.supp
	echo "   IgnoreReadlineLeak" >> ~/.supp.supp
	echo "   Memcheck:Leak" >> ~/.supp.supp
	echo "   match-leak-kinds: reachable" >> ~/.supp.supp
	echo "   ..." >> ~/.supp.supp
	echo "   fun:readline" >> ~/.supp.supp
	echo "   ..." >> ~/.supp.supp
	echo "}" >> ~/.supp.supp
	echo "{" >> ~/.supp.supp
	echo "   IgnoreReadlineLeak" >> ~/.supp.supp
	echo "   Memcheck:Leak" >> ~/.supp.supp
	echo "   ..." >> ~/.supp.supp
	echo "   fun:readline" >> ~/.supp.supp
	echo "   ..." >> ~/.supp.supp
	echo "}" >> ~/.supp.supp
	echo "{" >> ~/.supp.supp
	echo "   Malloc_Leak_Below_Main" >> ~/.supp.supp
	echo "   Memcheck:Leak" >> ~/.supp.supp
	echo "   fun:malloc" >> ~/.supp.supp
	echo "   ..." >> ~/.supp.supp
	echo "   obj:/usr/bin/*" >> ~/.supp.supp
	echo "}" >> ~/.supp.supp
	echo "{" >> ~/.supp.supp
	echo "   Calloc_Leak_Below_Main" >> ~/.supp.supp
	echo "   Memcheck:Leak" >> ~/.supp.supp
	echo "   fun:calloc" >> ~/.supp.supp
	echo "   ..." >> ~/.supp.supp
	echo "   obj:/usr/bin/*" >> ~/.supp.supp
	echo "}" >> ~/.supp.supp
	echo "{" >> ~/.supp.supp
	echo "   Realloc_Leak_Below_Main" >> ~/.supp.supp
	echo "   Memcheck:Leak" >> ~/.supp.supp
	echo "   fun:realloc" >> ~/.supp.supp
	echo "   ..." >> ~/.supp.supp
	echo "   obj:/usr/bin/*" >> ~/.supp.supp
	echo "}" >> ~/.supp.supp
	echo "use file supp to suppress valgrind errors: valgrind --suppressions="'"$$HOME/.supp.supp"'" ./minishell"

# Declare phony target
.PHONY: all clean fclean re supp
# Silence all commands
.SILENT:
# ANSI color codes
RED = \033[1;31m
GREEN = \033[1;32m
YELLOW = \033[1;33m
BLUE = \033[1;34m
NO_COLOR = \033[0m
BOLD = \033[1m
