CXX = g++
CPPFLAGS = -std=c++14 -Wpedantic -Wall -Wextra
CPPFLAGS += -O2
#CPPFLAGS += -fsanitize=address -fno-omit-frame-pointer -g
SOURCE = $(wildcard ../src/*.cpp)
OBJECTS = $(patsubst ../src/%.cpp, %.o, $(SOURCE))

all: game

game: $(OBJECTS)
	$(CXX) $(CPPFLAGS) $(OBJECTS) -o game

%.o: ../src/%.cpp
	$(CXX) $(CPPFLAGS) -c $< -o $@

clean:
	rm -f *.o game

