NAME		:= cub3d

DIR_OBJS	:= .objs
DIR_SRCS	:= src
DIR_INCS	:= include
DIR_LIBFT	:= lib/libft
DIR_MLX		:= lib/mlx

CC			:= gcc
CSAN		:= -fsanitize=address -g3
CFLAGS		:= -Wall -Wextra -Werror -g3
RM			:= rm -rf

LST_SRCS	:= check_map.c tmp.c main.c ft_mlx.c parsing.c player.c ft_hook.c
LST_OBJS	:= $(LST_SRCS:.c=.o)
LST_INCS	:= cub3d.h

SRCS		:= $(addprefix $(DIR_SRCS)/,$(LST_SRCS))
OBJS		:= $(addprefix $(DIR_OBJS)/,$(LST_OBJS))
INCS		:= $(addprefix $(DIR_INCS)/,$(LST_INCS))

all: deps $(NAME)

deps:
	@$(MAKE) --no-print-directory -C $(DIR_LIBFT)
	@$(MAKE) --no-print-directory -C $(DIR_MLX)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $^ -o $@  $(DIR_LIBFT)/libft.a $(DIR_MLX)/libmlx.a $(MLXFLAGS) -lX11 -lXext -L${DIR_MLX}

$(DIR_OBJS)/%.o: $(DIR_SRCS)/%.c $(INCS) Makefile $(DIR_INCS)/$(LST_INCS)| $(DIR_OBJS)
	$(CC) $(CFLAGS) -I $(DIR_INCS) -Imlx  -c $< -o $@

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