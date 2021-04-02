NAME = libasm.a
SRCS =  ft_strlen.s\
		ft_strcpy.s\
		ft_strcmp.s\
		ft_write.s\
		ft_read.s\
		ft_strdup.s

OBJS = $(SRCS:.s=.o)
NASM = nasm -f macho64
TEST = test

.PHONY: all, clean, fclean, re

%.o: %.s
	$(NASM) $< -o $@

%.o: %.c
	clang -Wall -Wextra -Werror $< -o $@

all: $(NAME)

$(NAME): $(OBJS)
	ar rcs libasm.a $(OBJS)

$(TEST): all
	clang -Wall -Wextra -Werror libasm.a main.c && ./a.out

clean:
	rm -rf $(OBJS) a.out my.txt real.txt

fclean: clean
	rm -rf $(NAME)

re: fclean all
