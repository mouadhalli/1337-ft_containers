.PHONY: all clean vector map stack

FLAGS = -Wall -Wextra -Werror -std=c++98

all: vector stack 

vector:
	@c++ $(FLAGS) tests/vector_test.cpp -o vector.out

stack:
	@c++ $(FLAGS) tests/stack_test.cpp -o stack.out

map:
	@c++ $(FLAGS) tests/map_test.cpp -o map.out


clean:
	@rm -rf map.out stack.out vector.out

fclean: clean

re: fclean all