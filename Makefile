CXX := g++
CXXFLAGS := -Wall -Wextra -std=c++20 -g

SRCS := src/main.cpp src/Lox/Lox.cpp src/Scanner/Scanner.cpp src/Token/Token.cpp 
OBJS := $(SRCS:.cpp=.o)
BIN := cpplox

all: $(BIN)

$(BIN): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(BIN)

