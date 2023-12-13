.SUFFIXES : .c .o

NAME = raytracer

CC = cc
CFLAGS = -Wall -Wextra -Werror
MEMORY = -g3 -fsanitize=address
LLDB = -g

RM = rm -f
INCLUDE = -I./include

SRCS = \
	src/main.c \
	src/print/print.c \
	src/scene/canvas.c \
	src/scene/camera.c \
	src/scene/object_create.c \
	src/trace/ray.c \
	src/trace/hit/hit.c \
	src/trace/hit/normal.c \
	src/trace/ray/phong_lighting.c \
	src/utils/vec3_utils.c \
	src/utils/object_utils.c
OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $^ -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $< $(INCLUDE)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re:
	$(MAKE) fclean
	$(MAKE) all

.PHONY: all clean fclean re
