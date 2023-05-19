SRCS	=	ft_atoi ft_bzero ft_calloc ft_isalnum ft_isalpha ft_isascii \
			ft_isdigit ft_isprint ft_memchr ft_memcmp ft_memmove ft_memset \
			ft_strchr ft_strlen ft_strnstr ft_strrchr ft_tolower ft_toupper \
			ft_memcpy ft_strdup ft_strlcat ft_strlcpy ft_strncmp ft_substr \
			ft_putnbr_fd ft_strjoin ft_strtrim ft_putchar_fd ft_putnbr_fd \
			ft_putstr_fd ft_putendl_fd ft_itoa ft_split ft_striteri ft_strmapi get_next_line get_next_line_utils

BONUS	=	ft_lstnew.c ft_lstsize.c ft_lstmap.c ft_lstlast.c ft_lstiter.c ft_lstdelone.c \
			ft_lstclear.c ft_lstadd_front.c ft_lstadd_back.c $(SRCS)

BONUS_OBJS	=	${BONUS:.c=.o}

NAME = libft.a

OBJ_DIR = obj/
SRC_DIR = src/

INCLUDES = -I 

SRC = $(addprefix $(SRC_DIR), $(addsuffix .c, $(SRCS)))
OBJS = $(addprefix $(OBJ_DIR), $(addsuffix .o, $(SRCS)))

CC = gcc

CFLAGS = -Wall -Wextra -Werror

AR = ar rc

RM = rm -f

OBJF = .cache_exits

$(OBJF) :
	@mkdir -p $(OBJ_DIR)

${NAME}:	${OBJS}
			$(AR) ${NAME} ${OBJS}

$(OBJ_DIR)%.o : $(SRC_DIR)%.c | $(OBJF)
	$(CC) $(CFLAGS) -c $< -o $@

all:		${NAME}

clean:
			${RM} ${OBJS} $(BONUS_OBJS)

fclean:		clean
			${RM} ${NAME}

bonus:		${BONUS_OBJS}
			${AR} ${NAME} ${BONUS_OBJS}

re: fclean all

.PHONY:		all clean fclean re bonus