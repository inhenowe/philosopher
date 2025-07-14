# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aleortiz <aleortiz@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/04/29 12:27:28 by aleortiz          #+#    #+#              #
#    Updated: 2025/06/30 09:23:21 by aleortiz         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# name              #
NAME = philo
#===================#

# color constants    #
RESET = \033[0m
BLACK = \033[0;30m
RED = \033[0;31m
GREEN = \033[0;32m
YELLOW = \033[0;33m
BLUE = \033[0;34m
MAGENTA = \033[0;35m
CYAN = \033[0;36m
WHITE = \033[0;37m
#=====================#

# color bolds         #
B_BLACK = \033[1;30m
B_RED = \033[1;31m
B_GREEN = \033[1;32m
B_YELLOW = \033[1;33m
B_BLUE = \033[1;34m
B_MAGENTA = \033[1;35m
B_CYAN = \033[1;36m
B_WHITE = \033[1;37m
#=====================#

# text utilities         #
FAINT = \033[2m
ITALIC = \033[3m
UNDERLINE = \033[4m
BLINK = \033[5m
INVERT = \033[7m
HIDDEN = \033[8m
STRIKE = \033[9m
#========================#

# Paths to headers and source files     #
HEADER = ./philosopher
SOURCE = ./src
OBJSD = ./OBJ
#=======================================#

# Archivos fuente y crear objetos   ====================#
FILES = $(addprefix $(SOURCE)/,	assets.c\
								algoritm.c\
								ArgCheck.c\
								utilities.c\
								errorsLogs.c\
								philosopher.c\
								algorimos_2.c)

OBJS = $(addprefix $(OBJSD)/, $(notdir $(FILES:.c=.o)))
#=======================================================#

# Compiladores y flags    ==========================================================#
CC = cc
CFLAGS = -g -Wall -Werror -Wextra
INCFLAGS = -I$(HEADER)
HELGRIND = valgrind --tool=helgrind --history-level=approx -s
DELGRIND = valgrind --tool=drd
#===================================================================================#

all:$(NAME)

$(NAME) : $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) $(INCFLAGS) -o $(NAME)
	@echo "$(B_GREEN)$(BLINK)$(INVERT)✅ ALL DONE SUCCESFULY ✅$(RESET)"

$(OBJSD)/%.o : $(SOURCE)/%.c | $(OBJSD)
	@$(CC) $(CFLAGS) -c $< -o $@
	@OBJCOUNT=$$(ls $(OBJSD) | wc -l); \
	PERCENT=$$((($$OBJCOUNT * 100)/7)); \
	echo "$(B_MAGENTA)🛠️ [$$PERCENT%]Compiling $< to $@ 🛠️$(RESET)"
	@sleep 0.2

$(OBJSD) :
	@mkdir -p $(OBJSD)

clean :
	@if [ -e $(OBJSD) ]; then \
		echo "$(B_RED)$(STRIKE)🗑️ assets.o\
								\n🗑️ algoritm.o\
								\n🗑️ ArgCheck.o\
								\n🗑️ utilities.o\
								\n🗑️ errorsLogs.o\
								\n🗑️ philosopher.o$(RESET)"; \
		echo "$(B_RED)$(BLINK)$(INVERT)🚨 ALL DELETE SUCCESFULY 🚨$(RESET)"; \
		rm -rf $(OBJSD); \
	fi
	@if [ -e DATA.txt ]; then \
		rm -rf DATA.txt ;\
	fi

fclean : clean
	@rm -rf $(NAME)

DATA_RACE :
	@$(HELGRIND) ./$(NAME) $(AV) > DATA.txt 2>&1

re : fclean all

.PHONY : all clean fclean DATA_RACE
