
NAME= "npuzzle"

SRC= Solvability.cpp parser.cpp solver.cpp program.cpp
OBJ= $(SRC:.cpp=.o)
SRC_PATH=./src/
OBJ_PATH=./obj/
SRCS=$(addprefix $(SRC_PATH), $(SRC))
OBJS=$(addprefix $(OBJ_PATH), $(OBJ))
CXX= clang++
CXXFLAGS= -Wall -Werror -Wextra

.phony: all clean fclean re

all: $(NAME)


$(NAME): $(OBJS)
	$(CXX) $(CXXFLAGS) $^ -o $@

$(OBJ_PATH)%.o: $(SRC_PATH)%.cpp
	@mkdir $(OBJ_PATH) 2> /dev/null || true
	$(CXX) $(CXXFLAGS) -c $^ -o $@

clean:
	rm -rf $(OBJS)
	@rmdir $(OBJ_PATH) 2> /dev/null || true

fclean: clean
	rm -rf $(NAME)

re: fclean all