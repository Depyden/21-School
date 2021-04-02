# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lregenar <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/08/12 20:53:36 by lregenar          #+#    #+#              #
#    Updated: 2019/08/12 21:04:17 by lregenar         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a
SRCS = srcs/
INCLUDES = includes/
FUNCTIONS = ft_putchar ft_putstr ft_strcmp ft_strlen ft_swap
BINS = $(patsubst %, %.o, $(FUNCTIONS))

.PHONY: clean fclean re all

all: $(NAME)
	$(BINS): @gcc -Wall -Wextra -Werror -c $(patsubst %.o, $(SRCS)%.c, $@) -I $(INCLUDES)
	
$(NAME): $(BINS)
	@ar rc $(NAME) $(BINS);
	@ranlib $(NAME);

clean:
	@rm -f $(BINS)

fclean: clean
	@rm -f $(NAME)

re : fclean all
