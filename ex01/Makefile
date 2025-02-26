# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fcoullou <fcoullou@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/12/27 15:54:12 by fcoullou          #+#    #+#              #
#    Updated: 2025/02/25 14:23:02 by fcoullou         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

################################################################################
##	PROG NAME	################################################################
NAME			= RPN

################################################################################
##	FILES		################################################################
SRC				=  main.cpp RPN.cpp
#------------------------------------------------------------------------------#
OBJ				= $(addprefix $(OBJDEP_DIR)/, $(SRC:.cpp=.o))
DEP 			= $(OBJ:%.o=%.d)
#------------------------------------------------------------------------------#
OUTPUT_LEAKS 	= valgrind-out.txt

##	DIRECTORIES		############################################################
OBJDEP_DIR      = objdep

################################################################################
##	COMPILER	################################################################
##	-Wall : Active tous les avertissements (-Wall).
##	-Werror : Traite les avertissements comme des erreurs (-Werror).
##	-Wextra : Active des avertissements supplémentaires (-Wextra).
##	-g3 : Génère des informations de débogage détaillées dans le fichier exécutable.
##	-ftrapv : Génère des erreurs d'exécution en cas de débordement arithmétique.
##	-std=c++98 : Utilise la norme C++98.
CFLAGS			= -Wall -Werror -Wextra -I./include -g3 -std=c++98
# -ftrapv
# -fsanitize=undefined -fsanitize=address

##	-MMD : Génère des fichiers .d avec des dépendances pour chaque fichier source,
## utile pour la recompilation conditionnelle avec make.
##	-c : Compile les fichiers source sans les lier, générant des fichiers objet (.o).
CPPFLAGS		= -MMD -c

#------------------------------------------------------------------------------#
AR				= ar
CXX				= c++
RM				= rm -f
CD				= cd
DIR_DUP			= mkdir -p $(@D)

################################################################################
##	+++++		################################################################
GREEN=\033[0;32m
RED=\033[0;31m
RESET=\033[0m
CLEAR_EOL=\033[K
CLEAR_EOL_FROM_CURSOR=; tput el; printf 
#------------------------------------------------------------------------------#
VALCHECK=--leak-check=full
VALSHOW=--show-leak-kinds=all
VALFD=--track-fds=yes
VALIGNORE=--suppressions=valgrind_readline_leaks_ignore.txt
VALCHILD=--trace-children=yes

################################################################################
##	RULES		################################################################
all: $(NAME)

$(NAME): $(OBJ)
	@$(CXX) $(CFLAGS) $(OBJ) -o $(NAME)
	@printf "$(GREEN)[CREATED]$(RESET) : $(NAME)" $(CLEAR_EOL_FROM_CURSOR) "\n"

$(OBJDEP_DIR)/%.o: %.cpp | $(OBJDEP_DIR)
	@printf "$(GREEN)[COMPILATION]$(RESET) : $<$(CLEAR_EOL)\r"
	@$(CXX) $(CFLAGS) $(CPPFLAGS) -o $@ -c $< 
	
$(OBJDEP_DIR):
	@mkdir -p $@

#------------------------------------------------------------------------------#
clean:
	@deleted=0; \
	for file in $(OBJ); do \
        if [ -f $$file ]; then \
            printf "$(RED)[DELETE FILES]$(RESET) : $(CLEAR_EOL)$$file "; \
            sleep 0.01; \
            printf "\r"; \
            $(RM) $$file; \
            deleted=1; \
        fi; \
    done; \
    if [ $$deleted -eq 1 ]; then \
        printf "$(CLEAR_EOL)$(RED)[ALL FILES DELETED]$(RESET)\n"; \
    else \
        printf "$(CLEAR_EOL)make: *** All files already deleted ***$(RESET)\n"; \
	fi
	@$(RM) -r $(OBJDEP_DIR) $(OUTPUT_LEAKS)
    
#------------------------------------------------------------------------------#
fclean: clean
	@if [ -f $(NAME) ]; then \
        $(RM) -f $(NAME); \
    fi
	
#------------------------------------------------------------------------------#
re: fclean all

#------------------------------------------------------------------------------#
test: all
	./$(NAME) $(ARG)
	
#------------------------------------------------------------------------------#
leaks: all
	valgrind $(VALIGNORE) $(VALSHOW) $(VALCHECK) ./$(NAME)
	@cat valgrind-out.txt
	
#------------------------------------------------------------------------------#
valgrind : all
	valgrind $(VALIGNORE) $(VALSHOW) $(VALCHECK) $(VALCHILD) $(VALFD) ./${NAME}

#------------------------------------------------------------------------------#
.PHONY: all bonus clean fclean re test leaks  

#------------------------------------------------------------------------------#

-include $(DEP)