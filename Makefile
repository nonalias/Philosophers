NAME	=	philo_one

SRCS	=	proto.c \
			init.c	\
			utils.c \

CC		=	gcc
CFLAGS	=	-Wall -Wextra -Werror
HDR		=	-include ./philo_one.h
OBJS	=	$(SRCS:%.c=%.o)

all		:	$(NAME)

go		:	all
	./philo_one 5 800 200 200 3

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
