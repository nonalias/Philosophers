NAME	=	philo_three

SRCS	=	philo_three.c \
			init.c	\
			utils.c \
			utils2.c \
			valid_check.c \
			callback.c \
			time.c \

CC		=	gcc
CFLAGS	=	-Wall -Wextra -Werror
HDR		=	-include ./philo_three.h
OBJS	=	$(SRCS:%.c=%.o)

all		:	$(NAME)

go		:	all
	./philo_three 5 800 200 200 3

$(NAME)	:	$(OBJS)
	$(CC) $(CFLAGS) $(HDR) -o $@ $(OBJS)

debug	:	$(OBJS)
	$(CC) $(CFLAGS) $(HDR) -o $@ $(OBJS) -g3 -fsanitize=address

%.o		:	%.c
	$(CC) $(CFLAGS) $(HDR) -o $@ -c $<

clean	:
	rm -f $(OBJS)

fclean	:	clean
	rm -f $(NAME) 

re		:	fclean	all

.PHONY	:	all clean fclean re
