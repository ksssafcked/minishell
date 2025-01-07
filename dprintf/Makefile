SRC = ft_printf.c ft_printf_unsigned_int.c ft_printf_str.c ft_printf_ptr.c ft_printf_nbr.c ft_printf_char.c ft_printf_base_unsigned.c
OBJ = ${SRC:.c=.o}
CC = gcc
FLAGS = -Wall -Wextra -Werror
NAME = libftprintf.a

all : ${NAME}

${NAME}: ${OBJ}
	ar rcs ${NAME} ${OBJ}

${OBJ} :
	${CC} ${FLAGS} -c ${@:.o=.c} -o ${@:.c=.o}

clean :
	rm -f ${OBJ}

fclean : clean
	rm -f ${NAME}

re : fclean all

.PHONY: all clean fclean re
