NAME    = regression

CXX     = c++
CXXFLAGS = -Wall -Wextra -Werror -std=c++17

SRCS    = main.cpp data.cpp linear_regression.cpp gradient_descend.cpp
OBJS    = $(SRCS:.cpp=.o)
HEADERS = data.hpp linear_regression.hpp gradient_descend.hpp

all: $(NAME)

$(NAME): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(NAME) $(OBJS)

%.o: %.cpp $(HEADERS)
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
