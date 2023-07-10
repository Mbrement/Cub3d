NAME := cub3d

DIR_OBJS := .objs
DIR_SRCS := src
DIR_INCS := incs
DIR_LIBFT := libft
DIR_MLX := mlx

CC := gcc
CSAN := -fsanitize=address -g3
CFLAGS := -Wall -Wextra -Werror
RM := rm -rf

LST_SRCS := $(wildcard $(DIR_SRCS)/*/*.c)
LST_OBJS := $(LST_SRCS:$(DIR_SRCS)/%.c=$(DIR_OBJS)/%.o)
LST_INCS := include.h

SRCS := $(LST_SRCS)
OBJS := $(LST_OBJS)
INCS := $(addprefix $(DIR_INCS)/,$(LST_INCS))

all: deps $(NAME)

deps:
	@$(MAKE) --no-print-directory -C $(DIR_LIBFT)
	@$(MAKE) --no-print-directory -C $(DIR_MLX)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $^ -o $@  $(DIR_LIBFT)/libft.a $(DIR_MLX)/libmlx.a $(MLXFLAGS)

$(DIR_OBJS)/%.o: $(DIR_SRCS)/%.c $(DIR_INCS)/$(LST_INCS) | $(DIR_OBJS)
	$(CC) $(CFLAGS) -I $(DIR_INCS) -Imlx -c $< -o $@

$(DIR_OBJS):
	mkdir -p $(DIR_OBJS)

clean:
	$(RM) $(DIR_OBJS)
	make clean -C ${DIR_LIBFT}
	make clean -C ${DIR_MLX}

fclean: clean
	$(RM) $(NAME)
	make fclean -C ${DIR_LIBFT}
	make clean -C ${DIR_MLX}

re: fclean all