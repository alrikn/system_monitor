##
## EPITECH PROJECT, 2025
## pool tek 2
## File description:
## Makefile
##

NAME = MyGKrellm
SRC = CpuModule.cpp \
	main.cpp



OBJ = $(SRC:.cpp=.o)
CXX = clang++
CXXFLAGS = -std=c++20 -Wall -Wextra -Werror -g
LIB_FLAGS = -lncurses

all: $(NAME)

$(NAME): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $(NAME) $(OBJ) $(LIB_FLAGS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all
