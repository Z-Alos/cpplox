CXX := g++
CXXFLAGS := -Wall -Wextra -std=c++20 -g

SRCS := $(wildcard src/*.cpp)
OBJS := $(SRCS:.cpp=.o)
BIN := cpplox 

all: $(BIN)

$(BIN): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(BIN)

