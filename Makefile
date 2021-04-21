CXX = g++
CXXFLAGS = -std=c++0x  -Wall

OBJECTS = src/main.o src/node.o src/problem.o

8puzzle: $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $@ $^

