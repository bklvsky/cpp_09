# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dselmy <dselmy@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/15 13:49:13 by dselmy            #+#    #+#              #
#    Updated: 2023/05/15 14:08:00 by dselmy           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS			=	main.cpp \
					BitcoinExchange.cpp
OBJS			= $(SRCS:.cpp=.o)
DEP				= $(SRCS:.cpp=.d)

DB				= data.csv	

CXX				= c++
RM				= rm -rf
CXXFLAGS		= -std=c++98 -Wall -Wextra -Werror -I.

NAME			= btc

all:			$(NAME) $(DB)

data: $(DB)

$(DB):
	wget https://cdn.intra.42.fr/document/document/17907/cpp_09.tgz
	tar -xzf cpp_09.tgz
	mv ./cpp_09/$(DB) ./
	$(RM) ./cpp_09/ ./cpp_09.tgz

$(NAME):		$(OBJS)
				$(CXX) $(CXXFLAGS) -o $(NAME) $(OBJS)

%.o:			%.cpp
				$(CXX) -c $(CXXFLAGS) $< -o $@ -MD

clean:
				$(RM) $(OBJS) $(DEP)

fclean:			clean
				$(RM) $(NAME) $(DB)

re:				fclean $(NAME)

include $(wildcard $(DEP))

.PHONY:			all clean fclean re
