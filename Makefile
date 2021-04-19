CXX = g++
CXXFLAGS = -std=c++0x -Wall

OBJECTS = src/main.o src/node.o

8puzz: $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $@ $^

