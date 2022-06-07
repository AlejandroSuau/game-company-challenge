
#include <vector>
#include <memory>
#include <iostream>

#include "Map.h"
#include "MapWalker.h"
#include "Heuristic.h"

#include "BinaryHeap.h"


// API Function given:
bool FindPath(std::pair<int, int> Start,
              std::pair<int, int> Target,
              const std::vector<int>& Map,
              std::pair<int, int> MapDimensions,
              std::vector<int>& OutPath);

int main(int argc, const char * argv[]) {
    std::pair<int, int> map_dimensions = {10, 6};
    std::vector<int> map_locations = {
        1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
        1, 0, 0, 0, 0, 0, 0, 1, 1, 1,
        1, 0, 1, 1, 1, 1, 1, 1, 1, 1,
        1, 0, 1, 0, 0, 0, 1, 1, 0, 1,
        1, 0, 1, 0, 1, 1, 1, 1, 0, 1,
        1, 1, 1, 0, 1, 1, 1, 1, 0, 1,
    };
    const Map map(map_dimensions, map_locations);
    MapWalker map_walker(map, {0, 5}, {9, 5}, std::make_unique<Manhattan>());
    
    /*std::pair<int, int> map_dimensions = {5, 4};
    std::vector<int> map_locations = {
        1, 0, 1, 0, 1,
        1, 0, 1, 0, 1,
        1, 0, 1, 1, 1,
        1, 1, 1, 1, 1,
    };
    const Map map(map_dimensions, map_locations);
    MapWalker map_walker(map, {0, 0}, {4, 3}, std::make_unique<Manhattan>());*/
    map_walker.FindPath();
    
    
     // Testing solution print.
     for (int i = 0; i < map_dimensions.second; ++i) { // row
        for (int j = 0; j < map_dimensions.first; ++j) { // col
            const auto index = i * map_dimensions.first + j;
            if (std::find(map_walker.out_path_.begin(),
                          map_walker.out_path_.end(), index)
                != map_walker.out_path_.end()) {
                std::cout << " x ";
            } else {
                if (map.IsTraversable(index))
                    std::cout << " - ";
                else
                    std::cout << " 0 ";
            }
        }
        std::cout << std::endl;
    }
    
    return 0;
}
