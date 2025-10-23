# **************************************************************************** #
#                            EXPERIMENTAL MAKEFILE                             #
# **************************************************************************** #

# Colors for output
RED			= \033[0;31m
GREEN		= \033[0;32m
YELLOW		= \033[0;33m
BLUE		= \033[0;34m
PURPLE		= \033[0;35m
CYAN		= \033[0;36m
RESET		= \033[0m

# Project info
NAME		= cub3D
BONUS_NAME	= cub3D_bonus

# Compiler settings
CC			= cc
CFLAGS		= -Wall -Wextra -Werror
DEBUG_FLAGS	= -g3 -fsanitize=address
OPT_FLAGS	= -O2
RM			= rm -rf

# MiniLibX paths (adjust based on your system)
MLX_LINUX	= minilibx-linux
MLX_MAC		= minilibx-macos

# Auto-detect OS and set MLX path
UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S),Linux)
    MLX_PATH = $(MLX_LINUX)
    MLX = minilibx/libmlx_Linux.a
    MLX_FLAGS = -Lminilibx -lmlx -lX11 -lXext -lm
else ifeq ($(UNAME_S),Darwin)
    MLX_PATH = $(MLX_MAC)
    MLX = minilibx/libmlx.a
    MLX_FLAGS = -Lminilibx -lmlx -framework OpenGL -framework AppKit
endif

# Library paths
LIBFT_PATH	= libft
LIBFT		= $(LIBFT_PATH)/libft.a

# Source directories
SRC_DIR		= src
OBJ_DIR		= obj
BONUS_DIR	= bonus

# Source files (auto-discovered)
SRC			= $(shell find $(SRC_DIR) -name "*.c" -type f)
OBJ			= $(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

# Bonus files (if you implement bonuses)
BONUS_SRC	= $(shell find $(BONUS_DIR) -name "*.c" -type f 2>/dev/null || true)
BONUS_OBJ	= $(BONUS_SRC:$(BONUS_DIR)/%.c=$(OBJ_DIR)/%.o)

# Includes
INCLUDES	= -Iincludes -I$(LIBFT_PATH) -Iminilibx

# Progress bar variables
TOTAL_FILES = $(words $(SRC))
COMPILED = 0
define progress_bar
	$(eval COMPILED=$(shell echo $$(($(COMPILED)+1))))
	@printf "\r[$(CYAN)%-20s$(RESET)] %d/%d" \
		"$(shell printf '▓%.0s' $$(seq 1 $$(echo "scale=0; $(COMPILED)*20/$(TOTAL_FILES)" | bc)))" \
		$(COMPILED) $(TOTAL_FILES)
endef

# **************************************************************************** #
#                               MAIN TARGETS                                   #
# **************************************************************************** #

all: header libft mlx $(NAME)
	@echo "$(GREEN)\n✅ $(NAME) compiled successfully!$(RESET)"

$(NAME): $(OBJ) $(LIBFT) $(MLX)
	@$(CC) $(CFLAGS) $(OBJ) $(LIBFT) $(MLX_FLAGS) -o $(NAME)
	@echo "\n\n$(GREEN)✅ Executable created: $(NAME)$(RESET)"

bonus: header libft mlx $(BONUS_NAME)
	@echo "$(GREEN)\n✅ $(BONUS_NAME) compiled successfully!$(RESET)"

$(BONUS_NAME): $(BONUS_OBJ) $(LIBFT) $(MLX)
	@echo "$(YELLOW)\n🔗 Linking $(BONUS_NAME)...$(RESET)"
	@$(CC) $(CFLAGS) $(BONUS_OBJ) $(LIBFT) $(MLX_FLAGS) -o $(BONUS_NAME)

# Object file compilation with progress bar (SIMPLIFICADO)
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	@$(call progress_bar)
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(OBJ_DIR)/%.o: $(BONUS_DIR)/%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

# **************************************************************************** #
#                              LIBRARY TARGETS                                 #
# **************************************************************************** #

libft:
	@echo "$(BLUE)📚 Compiling libft...$(RESET)"
	@$(MAKE) -C $(LIBFT_PATH) --no-print-directory --silent

mlx:
	@echo "$(BLUE)🎨 Compiling MiniLibX...$(RESET)"
	@if [ -d "$(MLX_PATH)" ]; then \
		$(MAKE) -C $(MLX_PATH) --no-print-directory --silent > /dev/null 2>&1; \
		mkdir -p minilibx; \
		cp $(MLX_PATH)/libmlx* minilibx/ 2>/dev/null || true; \
		echo "$(GREEN)✅ MiniLibX ready$(RESET)\n"; \
	else \
		echo "$(YELLOW)⚠️  MiniLibX not found at $(MLX_PATH)$(RESET)"; \
		echo "$(YELLOW)   Please install it or check the path$(RESET)"; \
	fi

# **************************************************************************** #
#                              DEVELOPMENT TARGETS                             #
# **************************************************************************** #

debug: CFLAGS += $(DEBUG_FLAGS)
debug: all
	@echo "$(YELLOW)🔧 Debug version compiled with AddressSanitizer$(RESET)"

fast: CFLAGS += $(OPT_FLAGS)
fast: all
	@echo "$(GREEN)⚡ Optimized version compiled$(RESET)"

test: all
	@echo "$(CYAN)🧪 Running tests...$(RESET)"
	@./$(NAME) maps/test.cub || true

valgrind: debug
	@echo "$(PURPLE)🔍 Running valgrind...$(RESET)"
	@valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./$(NAME) maps/test.cub

# **************************************************************************** #
#                                CLEAN TARGETS                                 #
# **************************************************************************** #

clean:
	@echo "$(RED)🧹 Cleaning object files...$(RESET)"
	@$(RM) $(OBJ_DIR)
	@$(MAKE) -C $(LIBFT_PATH) clean --no-print-directory --silent
	@if [ -d "$(MLX_PATH)" ]; then \
		$(MAKE) -C $(MLX_PATH) clean --no-print-directory --silent 2>/dev/null || true; \
	fi

fclean: clean
	@echo "$(RED)🗑️  Removing executables and libraries...$(RESET)"
	@$(RM) $(NAME) $(BONUS_NAME)
	@$(RM) minilibx
	@$(MAKE) -C $(LIBFT_PATH) fclean --no-print-directory --silent

re: fclean all

# **************************************************************************** #
#                                INFO TARGETS                                  #
# **************************************************************************** #

info:
	@echo "$(CYAN)📊 Project Information:$(RESET)"
	@echo "OS: $(UNAME_S)"
	@echo "MLX Path: $(MLX_PATH)"
	@echo "Source files: $(words $(SRC))"
	@echo "Bonus files: $(words $(BONUS_SRC))"
	@echo "Compiler: $(CC)"
	@echo "Flags: $(CFLAGS)"

header:
	@echo "$(PURPLE)"
	@echo "\n\n ██████╗██╗   ██╗██████╗ ██████╗ ██████╗ "
	@echo "██╔════╝██║   ██║██╔══██╗╚════██╗██╔══██╗ "
	@echo "██║     ██║   ██║██████╔╝ █████╔╝██║  ██║ "
	@echo "██║     ██║   ██║██╔══██╗ ╚═══██╗██║  ██║ "
	@echo "╚██████╗╚██████╔╝██████╔╝██████╔╝██████╔╝ "
	@echo " ╚═════╝ ╚═════╝ ╚═════╝ ╚═════╝ ╚═════╝ "
	@echo "\n\t$(BLUE)By fosuna-g & fsaffiri $(RESET)\n\n"

# **************************************************************************** #
#                                PHONY TARGETS                                 #
# **************************************************************************** #

.PHONY: all bonus clean fclean re libft mlx debug fast test valgrind info header