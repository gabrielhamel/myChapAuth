##
## EPITECH PROJECT, 2019
## PSU_strace_2018
## File description:
## Makefile
##

NAME =		client

CFLAGS +=	-I$(INC_DIR) -W -Wall -Wextra

SRC =		$(SRC_DIR)/main.c

SRC_DIR =	$(realpath src)

INC_DIR =	$(realpath include)

OBJ =		$(SRC:.c=.o)

RM =		@rm -rf

ECHO =		/bin/echo -e

DEFAULT =	"\033[00m"

GREEN =		"\033[1;32m"

TEAL =		"\033[1;37m"

RED =		"\033[1;33m"

SANG =		"\033[1;31m"

all:		titre $(NAME)

titre:
			@$(ECHO) $(RED)¶ Building $(NAME)$(TEAL):$(DEFAULT)

unit-tests:
			@$(ECHO) $(RED)¶ Building tests$(TEAL):$(DEFAULT)

$(NAME):	$(OBJ)
			@gcc -o $(NAME) $(OBJ) $(CFLAGS)  && $(ECHO) $(GREEN)✓$(TEAL)" BUILD SUCCESS !"$(TEAL) $(DEFAULT) || $(ECHO) $(SANG)✗$(TEAL)" BUILD FAILED !"$(TEAL) $(DEFAULT)

clean:
			@$(ECHO) $(RED)¶ Cleaning$(TEAL):$(DEFAULT)
			@$(ECHO) $(GREEN)  " [OK]" $(TEAL)"Clean obj"$(TEAL)
			$(RM) $(OBJ)
			@($(ECHO) $(GREEN)✓$(TEAL)" CLEAN SUCCESS !"$(TEAL))

fclean:		clean
			$(RM) $(NAME)

re:			fclean all

%.o : %.c
			@gcc -c -o $@ $^ $(CFLAGS) && $(ECHO) -n $(GREEN)"  [OK] "$(TEAL) || $(ECHO) -n $(SANG)"  [NO] "$(TEAL) && $(ECHO) $< | rev | cut -d'/' -f 1 | rev

.PHONY:		all fclean re clean