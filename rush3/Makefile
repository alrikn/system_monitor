##
## EPITECH PROJECT, 2025
## rush 3
## File description:
## rush 3
##

SRC	=	Data.cpp \
		DataGetters.cpp \
		Window.cpp	\

OBJ	=	$(SRC:.cpp=.o)

NAME	=	MyGKrellm

RM	=	rm -rf

CXX	=	g++
CXXFLAGS = -I./include/ -g -std=c++20 -Wall -Wextra
SFML_LIBS = -lsfml-window -lsfml-system -lsfml-graphics

all:	$(NAME)

$(NAME):	$(OBJ)
		$(CXX) $(OBJ) -o $(NAME) $(CXXFLAGS) $(SFML_LIBS)

clean:
		$(RM) $(OBJ)

fclean:	clean
		$(RM) $(NAME)

re:		fclean all
