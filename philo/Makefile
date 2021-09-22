# Folders

override BIN		:= bin
override SRC		:= src
override INC		:= includes

# Properties

NAME				= philo

# Commands

override CC			:= clang
override RM			:= rm -rf
override CFLAGS		:= -Wall -Wextra -Werror
override INCLUDES	:= -I$(INC)

# Sources

override SRCS		:=							\
				exit.c							\
				main.c							\
				utils.c							\
				worker.c						\

override OBJS		:= $(addprefix $(BIN)/, $(SRCS:.c=.o))

override HEADERS	:= $(addprefix $(INC)/,		\
				philosophers.h					\
				)

# Rules

all:		$(NAME)

$(BIN)/%.o:	$(SRC)/%.c $(HEADERS)
			@mkdir -p $(dir $@);
			$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(NAME):	$(OBJS)
			clang $(CFLAGS) -o $@ $(OBJS)

clean:
			$(RM) $(OBJS)

fclean:		clean
			$(RM) $(NAME)

re:			fclean all

.PHONY:		all clean fclean re
