# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: algultse <algultse@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/05 13:15:55 by algultse          #+#    #+#              #
#    Updated: 2024/04/05 14:24:53 by algultse         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex
NAME_BONUS = $(NAME)

CC = cc
CFLAGS = -Wall -Wextra -Werror

LIBFTDIR = ./libft/
SRCDIR = ./srcs/
INCDIR = ./include/
OBJDIR = ./obj/
MANDATORYDIR = ./srcs/
BONUSDIR = ./bonus/

SRC = error.c init.c free.c cmd.c process.c
MANDATORY_SRC = $(MANDATORYDIR)main.c
BONUS_SRC = $(BONUSDIR)main_bonus.c
OBJS = $(SRC:%.c=$(OBJDIR)%.o)
MANDATORY_OBJS = $(OBJDIR)main.o
BONUS_OBJS = $(SRC:%.c=$(OBJDIR)%.o) $(BONUS_SRC:$(BONUSDIR)%.c=$(OBJDIR)%.o)

LIBFT = -L$(LIBFTDIR) -lft

all: libft $(NAME)

libft:
	@$(MAKE) -C $(LIBFTDIR)

$(NAME): $(OBJS) $(MANDATORY_OBJS)
	$(CC) $(OBJS) $(MANDATORY_OBJS) $(LIBFT) -o $(NAME)

bonus: libft $(BONUS_OBJS)
	$(CC) $(BONUS_OBJS) $(LIBFT) -o $(NAME_BONUS)

$(OBJDIR)%.o: $(SRCDIR)%.c
	mkdir -p $(OBJDIR)
	$(CC) $(CFLAGS) -I$(INCDIR) -I$(LIBFTDIR) -c $< -o $@

$(OBJDIR)main.o: $(MANDATORY_SRC)
	mkdir -p $(OBJDIR)
	$(CC) $(CFLAGS) -I$(INCDIR) -I$(LIBFTDIR) -c $< -o $@

$(OBJDIR)main_bonus.o: $(BONUS_SRC)
	mkdir -p $(OBJDIR)
	$(CC) $(CFLAGS) -I$(INCDIR) -I$(LIBFTDIR) -c $< -o $@

clean:
	rm -rf $(OBJDIR)
	@$(MAKE) -C $(LIBFTDIR) clean

fclean: clean
	rm -f $(NAME) $(NAME_BONUS)
	@$(MAKE) -C $(LIBFTDIR) fclean

re: fclean all

bonusre: fclean libft bonus

.PHONY: all clean fclean re bonus bonusre libft
