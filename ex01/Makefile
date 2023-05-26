# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dselmy <dselmy@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/15 13:49:13 by dselmy            #+#    #+#              #
#    Updated: 2023/05/21 17:49:42 by dselmy           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS			=	main.cpp \
					RPN.cpp
OBJS			= $(SRCS:.cpp=.o)
DEP				= $(SRCS:.cpp=.d)

CXX				= c++
RM				= rm -f
CXXFLAGS		= -std=c++98 -Wall -Wextra -Werror -I.

NAME			= RPN

all:			$(NAME)

$(NAME):		$(OBJS)
				$(CXX) $(CXXFLAGS) -o $(NAME) $(OBJS)

%.o:			%.cpp
				$(CXX) -c $(CXXFLAGS) $< -o $@ -MD

clean:
				$(RM) $(OBJS) $(DEP)

fclean:			clean
				$(RM) $(NAME)

re:				fclean $(NAME)

include $(wildcard $(DEP))

.PHONY:			all clean fclean re
