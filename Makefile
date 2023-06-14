SRCS	=	main.c\
			\
			error.c\
			check_map.c\

DIR_SRCS = src/

DIR_LIBFT	=	Libft/

DIR_OBJS = .objs/

DIR_HEAD = ./

OBJS	=	${SRCS:%.c=${DIR_OBJS}%.o}

CC	=	cc

MKDIR	=	mkdir -p

HEADERS	=	cub3d.h\
			libft/libft.h\

NAME	=	cub3D

LIBFT		=	libft.a

DIR_LIBFT	=	libft/

CFLAGS	= -Wall -Wextra -Werror 

all :		${NAME}

clean :		fclean_lib
			rm -rf ${DIR_OBJS}

fclean :	clean
			rm -rf ${NAME}

re :		fclean
			$(MAKE) all

${addprefix ${DIR_LIBFT}, ${LIBFT}}	:
		make ${LIBFT} -C ${DIR_LIBFT}

${DIR_OBJS}%.o:		${DIR_SRCS}%.c    ${addprefix ${DIR_HEAD}, ${HEADERS}} | ${DIR_OBJS}  ${addprefix ${DIR_LIBFT}, ${LIBFT}}
					${CC} ${CFLAGS} -I ${DIR_HEAD} -c $< -o $@

${DIR_OBJS}			:
					${MKDIR} ${DIR_OBJS}

${NAME}	:	${OBJS}
			${CC} ${CFLAGS} -o ${NAME} ${OBJS} -L${DIR_LIBFT} -lm


fclean_lib		:
					make fclean -C ${DIR_LIBFT}

normy : 
	norminette $(DIR_SRCS)$(SRCS)
	norminette $(HEADERS)



.PHONY:		all clean fclean re normy fclean_lib