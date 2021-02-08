NAME	=	philo_one

SRCS	=	proto.c \
			init.c	\
			utils.c \

CC		=	gcc
CFLAGS	=	-Wall -Wextra -Werror
HDR		=	-include ./philo_one.h
OBJS	=	$(SRCS:%.c=%.o)

go		:	all
	./philo_one 5 3  2 1

all		:	$(NAME)

$(NAME)	:	$(OBJS)
	$(CC) $(CFLAGS) $(HDR) -o $@ $(OBJS)

%.o		:	%.c
	$(CC) $(CFLAGS) $(HDR) -o $@ -c $<

clean	:
	rm -f $(OBJS)

fclean	:	clean
	rm -f $(NAME) 

re		:	fclean	all

.PHONY	:	all clean fclean re
