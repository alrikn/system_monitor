##
## EPITECH PROJECT, 2025
## pool tek 2
## File description:
## Makefile
##

NAME = MyGKrellm
SRC = main.cpp	\
		SFMLWindow.cpp
# SRC += CpuModule.cpp



OBJ = $(SRC:.cpp=.o)
CXX = clang++
CXXFLAGS = -std=c++20 -Wall -Wextra -g
LIB_FLAGS = -lncurses
SFML_LIBS = -lsfml-window -lsfml-system -lsfml-graphics

all: $(NAME)

$(NAME): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $(NAME) $(OBJ) $(LIB_FLAGS) $(SFML_LIBS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all
