CXX = g++
VPATH = ../src 
CPPFLAGS = -std=c++14 -Wpedantic -Wall -Wextra -Wmissing-prototypes -Wstrict-prototypes -Wconversion -Wshadow -Wcast-qual -Wnested-externs
CPPFLAGS += -fsanitize=address -fno-omit-frame-pointer -g

OBJECTS = \
    main.o BinaryHeap.o Heuristic.o Map.o MapWalker.o

all: game

game: $(OBJECTS)
	$(CXX) $(CPPFLAGS) $(OBJECTS) -o $@ $(LDFLAGS)

-include $(OBJECTS:.o=.d)

clean:
	rm -f *.o *.d game

