CXX = g++
VPATH = ../src 
CPPFLAGS = -std=c++11 -Wpedantic -Wall -Wextra -Wmissing-prototypes -Wstrict-prototypes -Wconversion -Wshadow -Wcast-qual -Wnested-externs
CPPFLAGS += -fsanitize=address -fno-omit-frame-pointer -g

OBJECTS = \
    BinaryHeap.o Heuristic.o Map.o PathFinder.o main.o

all: game

game: $(OBJECTS)
	$(CXX) $(CPPFLAGS) $(OBJECTS) -o $@ $(LDFLAGS)

-include $(OBJECTS:.o=.d)

clean:
	rm -f *.o *.d game

