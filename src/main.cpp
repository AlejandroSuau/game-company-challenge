
#include <vector>
#include <memory>
#include <iostream>
#include <queue>

#include "Map.h"
#include "PathFinder.h"
#include "Heuristic.h"

#include "BinaryHeap.h"


bool FindPath(std::pair<int, int> Start,
              std::pair<int, int> Target,
              const std::vector<int>& Map,
              std::pair<int, int> MapDimensions,
              std::vector<int>& OutPath);

int main(int argc, const char * argv[]) {
    /*std::pair<int, int> map_dimensions = {4, 3};
    std::vector<int> map_locations = {1, 1, 1, 1, 0, 1, 0, 1, 0, 1, 1, 1};
    const Map map(map_dimensions, map_locations);
    PathFinder path_finder(map, {0, 0}, {1, 2}, std::make_unique<Manhattan>());*/
    
    /*std::pair<int, int> map_dimensions = {1, 1};
    std::vector<int> map_locations = {1};
    const Map map(map_dimensions, map_locations);
    PathFinder path_finder(map, {0, 0}, {0, 0}, std::make_unique<Manhattan>());
    
    auto result = path_finder.FindPath();*/
    struct A {
        int value;
    };
    
    struct comparator {
    public:
        int operator()(const A& a, const A& b) {
            return (a.value > b.value);
        }
    };
    
    BinaryHeap<A, comparator> bh;
    bh.Push(A{1}); // 1
    bh.Push(A{3}); // 1, 3
    bh.Pop(); // 3
    
    bh.Push(A{4}); // 3, 4
    bh.Push(A{0}); // 0, 3, 4
    
    bh.Pop();
    bh.Pop();
    bh.Pop();
    
    return 0;
}
