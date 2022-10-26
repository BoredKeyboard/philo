# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: mforstho <mforstho@student.codam.nl>         +#+                      #
#                                                    +#+                       #
#    Created: 2022/10/10 11:12:37 by mforstho      #+#    #+#                  #
#    Updated: 2022/10/26 15:04:18 by mforstho      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME := philo
CC := gcc
CFLAGS ?= -Wextra -Wall -Werror -g # -fsanitize=address

SOURCES :=				\
	src/create_philos.c	\
	src/ft_atoi.c		\
	src/ft_isdigit.c	\
	src/ft_isspace.c	\
	src/ft_putendl_fd.c	\
	src/generic.c		\
	src/initialization.c\
	src/print_message.c	\
	src/threads.c		\
	src/philo.c

HEADERS := src/philo.h
OBJDIR := obj
OBJECTS := $(addprefix $(OBJDIR)/, $(SOURCES:c=o))

LIBFLAGS := -lpthread

INCLUDES := $(addprefix -I, $(sort $(dir $(HEADERS))))
CFLAGS += $(INCLUDES)

all : $(NAME)

$(NAME) : $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) $(LIBFLAGS) -o $(NAME)

$(OBJDIR)/%.o : %.c $(HEADERS)
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@

clean :
	rm -rf $(OBJDIR)

fclean : clean
	rm -f $(NAME)

re : fclean all

.PHONY : all clean fclean re
