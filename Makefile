NAME	=	pipex

SRCS	=	pipex.c	\
			main.c \
			handle_error.c \
			ft_split.c \
			ft_strlcpy.c \
			ft_strlen.c \
			ft_strchr.c \
			ft_strjoin.c \
			ft_strdup.c \
			ft_strncmp.c \
			guard_utils.c

INCS	=	pipex.h

OBJS	=	$(SRCS:%c=%o)

CC		=	cc
CFLAGS	=	-Wall -Werror -Wextra
AR		=	ar crs
RM		=	rm -f

.PHONY: all
all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(SRCS) -o $(NAME) -I $(INCS)

.PHONY: clean
clean:
	$(RM) $(OBJS)

.PHONY: fclean
fclean: clean
	$(RM) $(NAME)

.PHONY: re
re: fclean all
