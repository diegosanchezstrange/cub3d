NAME	= cub3d

CC		= gcc

CFLAGS	= -Wall -Werror -Wextra -O3 -D BUFFER_SIZE=32 -g3 -fsanitize=address

SRCS_MAIN	= main.c

SRCS_PARSE	= parse.c parse_map.c utils.c

SRCS_DISPLAY	= plot.c render.c  render_utils.c textures.c transform.c

SRCS_UTILS	= frees.c errors.c

SRCS		= ${SRCS_MAIN} \
				$(addprefix parse/, $(SRCS_PARSE)) \
				$(addprefix utils/, $(SRCS_UTILS)) \
				$(addprefix display/, $(SRCS_DISPLAY))

OBJS	= ${SRCS:.c=.o}

SRCS_DIR = src

OBJS_DIR = obj

OBJS_DIRS	= ${OBJS_DIR} \
				$(addprefix $(OBJS_DIR)/, parse) \
				$(addprefix $(OBJS_DIR)/, utils) \
				$(addprefix $(OBJS_DIR)/, display) \

LIBFT_NAME	= libft.a

MLX_NAME_MAC = libmlx.a

MLX_NAME_LINUX = libmlx_Linux.a

LIBFT	= lib/libft/

SRCS_PATHS 	= $(addprefix $(SRCS_DIR)/, $(SRCS))

OBJS_PATHS 	= $(addprefix $(OBJS_DIR)/, $(OBJS))

RM		= rm -rf

OS		:= $(shell uname -s)

ifeq (${OS},Linux)
	CFLAGS += -D LINUX
	MLX = lib/minilibx-linux/
	MLX_NAME = ${MLX_NAME_LINUX}
	LIBS = -lft -lmlx_Linux -lXext -lX11 -lm -lz
endif
ifeq (${OS},Darwin)
	CFLAGS += -D OSX
	MLX	= lib/minilibx_macos/
	MLX_NAME = ${MLX_NAME_MAC}
	LIBS = -lft -lmlx -framework OpenGL -framework AppKit
endif

MLX_LNK	= -L ${MLX}

LIB_LNK	= -L ${LIBFT}

INCLUDES = -I ./${LIBFT}inc -I ./${MLX} -I ./inc

all: ${NAME}

run: all
	./cub3d test_maps/ex.cub

${OBJS_DIR}/%.o: ${SRCS_DIR}/%.c
	${CC} ${CFLAGS} ${INCLUDES} -c $< -o $@ 

$(NAME): ${LIBFT_NAME} ${MLX_NAME} ${OBJS_DIRS} ${OBJS_PATHS} 
	${CC} ${CFLAGS} ${LIB_LNK} ${MLX_LNK} ${OBJS_PATHS} -o ${NAME} ${LIBS}

${LIBFT_NAME} :
	make -C ${LIBFT}
	cp ${LIBFT}/${LIBFT_NAME} .

${MLX_NAME} :
	make -C ${MLX}
	cp ${MLX}/${MLX_NAME} .

$(OBJS_DIRS):
	@mkdir -p $(OBJS_DIRS) 2> /dev/null

clean:
	@${RM} *.a ${OBJS_DIRS}/*.o *.dSYM
	@make clean -C ${LIBFT}
	@make clean -C ${MLX}

fclean:		clean
	@${RM} ${NAME}
	@make fclean -C ${LIBFT}

re:		fclean all

.PHONY:	clean re fclean all
