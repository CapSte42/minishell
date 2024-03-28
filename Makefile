# Target name
NAME = minishell
# Compiler
CC = cc
# Compilation flags
FLAGS = -g -ggdb -pedantic -Wall -Wextra -Werror -lreadline -Iinclude
EASYFLAGS = -g -ggdb -lreadline -Iinclude
# Library paths
LIBFT_PATH := ./libft
# Library files
LIBFT := $(LIBFT_PATH)/libft.a
# Source files
SRC = src/src_lexer/*.c \
	src/src_history/*.c \
	src/*.c
# Main target
$(NAME): $(LIBFT) $(SRC)
	if ! $(CC) $(SRC) $(FLAGS) $(LIBFT) -o $(NAME) 2>error.log; then \
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
	make -C $(LIBFT_PATH) all
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
# Push to git
push:
	git pull
	git add *
	git commit -m "$${MSG:-Generic update}"
	git push
# re then run
run: all
	if ! [ -e error.log ]; then \
		./$(NAME); \
	else \
		echo "${BOLD}${RED}Error log found${NO_COLOR}";\
	fi
# re then run with valgrind
run+: all
	if ! [ -e error.log ]; then \
		valgrind --suppressions=supp/readline.supp --leak-check=full --show-leak-kinds=all --track-origins=yes $${FLAG} ./$(NAME); \
	else \
		echo "${BOLD}${RED}Error log found${NO_COLOR}";\
	fi
# Declare phony target
.PHONY: all clean fclean re push run run+
# Silence all commands
.SILENT:
# ANSI color codes
RED = \033[1;31m
GREEN = \033[1;32m
YELLOW = \033[1;33m
BLUE = \033[1;34m
NO_COLOR = \033[0m
BOLD = \033[1m