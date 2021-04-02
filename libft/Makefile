# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: depyden <depyden@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/05/01 00:39:15 by depyden           #+#    #+#              #
#    Updated: 2020/05/13 16:31:16 by depyden          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.PHONY:  all clean fclean re

NAME=libft.a

SRCS =	ft_strlen.c ft_atoi.c ft_memset.c ft_strncmp.c ft_bzero.c ft_memcpy.c\
		ft_memccpy.c ft_memmove.c ft_memchr.c ft_memcmp.c ft_strchr.c ft_strrchr.c\
		ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isascii.c ft_isprint.c ft_toupper.c\
		ft_tolower.c ft_strdup.c ft_strcpy_bonus.c ft_calloc.c ft_strlcpy.c ft_strlcat.c\
		ft_strnstr.c ft_strcat_bonus.c ft_strjoin.c ft_itoa.c ft_putchar_fd.c\
		ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c ft_strndup_bonus.c ft_substr.c\
		ft_strncpy_bonus.c ft_strtrim.c ft_strmapi.c ft_split.c
			
OBJ	 = 	$(SRCS:.c=.o)

BONUS =	ft_lstnew.c ft_lstadd_front.c ft_lstsize.c ft_lstlast.c ft_lstadd_back.c\
		ft_lstdelone.c ft_lstclear.c ft_lstiter.c ft_lstmap.c

BONUSO = $(BONUS:.c=.o)

INCLUDES=./

FLAGS = -Wall -Wextra -Werror -c

%.o: %.c 
	@gcc $(FLAGS) $< -o $@
	
all: $(NAME)

$(NAME): $(OBJ)
	@ar rcs $(NAME) $(OBJ)

bonus: $(BONUSO)
	@ar rcs $(NAME) $(BONUSO)
	
clean:
	@rm -f $(OBJ) $(BONUSO)

fclean: clean
	@rm -f $(NAME)
	
re: fclean all
