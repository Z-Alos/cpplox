CXX := g++
CXXFLAGS := -Wall -Wextra -std=c++20 -g -MMD

SRCS := GenerateAST.cpp
OBJS := $(SRCS:.cpp=.o)
BIN := runMe

-include $(OBJS:.o=.d)

all: $(BIN)

$(BIN): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(BIN)


