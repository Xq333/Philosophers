	# **************************************************************************** #
	#                                                                              #
	#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
	#                                                     +:+ +:+         +:+      #
	#    By: pfaria-d <pfaria-d@student.42nice.fr>      +#+  +:+       +#+         #
	#                                                 +#+#+#+#+#+   +#+            #
	#    Created: 2023/03/19 11:52:41 by pfaria-d          #+#    #+#              #
#    Updated: 2023/06/12 13:13:56 by pfaria-d         ###   ########.fr        #
	#                                                                              #
	# **************************************************************************** #

NOCOLOR			= \033[0m
WHITE			= \033[1;37m
RED				= \033[0;31m
LIGHTPURPLE		= \033[1;35m
CLEAR			= \r\033[K
LIGHTGRAY		= \033[0;37m
GREEN			= \033[0;32m

SRC 		= src_bonus/main_bonus.c \
			  src_bonus/error_management_bonus.c \
			  src_bonus/utilities_bonus.c \
			  src_bonus/end_checker_bonus.c \
			  src_bonus/phases_bonus.c \

OBJS 		= $(SRC:.c=.o)

GCC 		= gcc

FLAGS		= -Wall -Wextra -Werror #-fsanitize=address
RM  = rm -f

NAME = philo_bonus

NORM = $(shell norminette | grep Error: | wc -l | awk '{print $1}' | xargs)

NORMINETTE = 0

ifeq (${NORM}, ${NORMINETTE})
	NORMINETTE = "${WHITE}NORM : ${GREEN}OK${NOCOLOR}\n"
else
	NORMINETTE = "${WHITE}NORM : ${RED}${NORM} errors${NOCOLOR}\n"
endif

all: 		$(NAME)

.c.o:
			@printf "${CLEAR}🌂 ${LIGHTPURPLE}%s ${LIGHTGRAY}compiling...${NOCOLOR}" ${notdir $<}
			@$(GCC) $(FLAGS) -c $< -o $(<:.c=.o)


$(NAME):	$(OBJS)
			@printf "${CLEAR}☂️  ${LIGHTPURPLE}Philosophers ${LIGHTGRAY}compiled\n${NOCOLOR}"
			@$(GCC) $(FLAGS) $(OBJS) -o $(NAME) 
			@echo ${NORMINETTE}

clean:
			@printf "${CLEAR}☂️  ${LIGHTPURPLE}.o files  ${LIGHTGRAY}cleaned\n${NOCOLOR}"
			@$(RM) $(OBJS) $(OBJSBONUS)

fclean:		clean
			@printf "${CLEAR}☂️  ${LIGHTPURPLE}Philosophers ${LIGHTGRAY}cleaned\n${NOCOLOR}"
			@$(RM) $(NAME)

datarace:	$(OBJS)
			@printf "${CLEAR}☂️  ${LIGHTPURPLE}Philosophers ${LIGHTGRAY}compiled\n${NOCOLOR}"
			@$(GCC) $(FLAGS) -g -fsanitize=thread  $(OBJS) -o $(NAME) 
			@echo ${NORMINETTE}

re:			fclean $(NAME)
