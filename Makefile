##
## EPITECH PROJECT, 2025
## pool tek 2
## File description:
## Makefile
##

NAME = MyGKrellm

SRC = main.cpp \
	src/Displays/BasicNcurses.cpp \
	src/Displays/SFMLWindow.cpp \
	src/Modules/BatteryModule.cpp \
	src/Modules/CpuModule.cpp \
	src/Modules/DateModule.cpp \
	src/Modules/HostModule.cpp \
	src/Modules/KernelModule.cpp \
	src/Modules/OsModule.cpp \
	src/Modules/RamModule.cpp \
	src/Modules/TimeModule.cpp \
	src/Modules/UptimeModule.cpp \
	src/Modules/UserModule.cpp

OBJ = $(SRC:.cpp=.o)

CXX = clang++
CXXFLAGS = -std=c++20 -Wall -Wextra -g
CPPFLAGS = -I include

LIB_FLAGS = -lncurses
SFML_LIBS = -lsfml-window -lsfml-system -lsfml-graphics

all: $(NAME)

$(NAME): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LIB_FLAGS) $(SFML_LIBS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all
