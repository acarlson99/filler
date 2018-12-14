#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: acarlson <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/11/20 15:33:04 by acarlson          #+#    #+#              #
#    Updated: 2018/12/14 02:09:21 by acarlson         ###   ########.fr        #
#                                                                              #
#******************************************************************************#

CC = clang
NAME = $(USER).filler
FILES = main populate_struct line_parsing map_parsing piece_parsing solve_map lstfuncs heatmap heatmap2
SRCS = srcs/
OBJDIR = .obj/
CFILES = $(addsuffix .c, $(FILES))
OFILES = $(addprefix $(OBJDIR), $(addsuffix .o, $(FILES)))
INCLUDES = -I includes -I libft/includes
CFLAGS = -Wall -Wextra -Werror
DFLAGS = -Wall -Wextra -g
LIBFT = libft.a
LIB = -L libft/ -lft

CL_CYAN = \033[0;36m
CL_GREEN = \033[0;32m
CL_RED = \033[0;31m
CL_WHITE = \033[0m

all: $(NAME)

$(NAME): $(OBJDIR) $(OFILES)
	@make -C libft/
	@$(CC) $(CFLAGS) $(INCLUDES) $(LIB) $(OFILES) -o $(NAME)
	@echo "  $(CL_WHITE)+ filler : Compiled $(CL_GREEN)$@$(CL_WHITE)"

clean:
	@make -C libft/ clean
	@echo " $(shell \
		if [ -d $(OBJDIR) ]; \
		then \
			echo " $(CL_WHITE)- filler : Removing $(CL_RED)$(OBJDIR)$(CL_WHITE) with$(CL_RED)"; \
			ls $(OBJDIR) | wc -w | tr -d '[:blank:]'; echo "$(CL_WHITE)object files"; \
			rm -Rf $(OBJDIR); \
		else \
			echo " $(CL_WHITE)# filler : Nothing to clean"; \
		fi) "

fclean: clean
	@make -C libft/ fclean
	@echo " $(shell \
		if [ -f $(NAME) ]; \
		then \
			echo " $(CL_WHITE)- filler : Removing  $(CL_RED)$(NAME)$(CL_WHITE)"; \
			rm -f $(NAME); \
		else \
			echo " $(CL_WHITE)# filler : Nothing to fclean"; \
		fi) "

re: fclean all

$(addprefix $(OBJDIR), %.o): $(addprefix $(SRCS), %.c)
	@$(CC) $(INCLUDES) $(CFLAGS) -o $@ -c $<

$(OBJDIR):
	@echo " $(shell \
	if [ -d $(OBJDIR) ]; \
	then \
		: ; \
	else \
		mkdir $(OBJDIR); \
		echo " + filler : Created  $(CL_GREEN)$(OBJDIR)$(CL_WHITE)$(CL_WHITE)"; \
	fi) "

debug:
	make -C libft/
	$(CC) $(DFLAGS) -D DEBUG $(INCLUDES) $(LIB) $(addprefix $(SRCS), $(CFILES)) -o $(NAME)

j: debug

dclean:
	rm $(NAME)
	rm -rf *.dSYM

leaks:
	make -C libft/
	$(CC) $(DFLAGS) -D LEAKS $(INCLUDES) $(LIB) $(addprefix $(SRCS), $(CFILES)) -o $(NAME)

lldb:
	make -C libft/
	$(CC) $(DFLAGS) -D LEAKS -D LLDB $(INCLUDES) $(LIB) $(addprefix $(SRCS), $(CFILES)) -o $(NAME)

fsan:
	make -C libft/
	$(CC) $(DFLAGS) -D DEBUG $(INCLUDES) $(LIB) $(addprefix $(SRCS), $(CFILES)) -o $(NAME) -fsanitize=address
