
#include <vector>
#include <memory>
#include <iostream>

#include "Map.h"
#include "MapWalker.h"
#include "Heuristic.h"


// API Function definition given:
bool FindPath(std::pair<int, int> start,
              std::pair<int, int> target,
              const std::vector<int>& map,
              std::pair<int, int> map_dimensions,
              std::vector<int>& out_path) {
    const Map custom_map(map_dimensions, map);
    const Map::Cell cell_start{start.first, start.second};
    const Map::Cell cell_target{target.first, target.second};
    MapWalker map_walker(custom_map,
                         cell_start,
                         cell_target,
                         out_path,
                         std::make_unique<Manhattan>());
    
    return map_walker.FindPath();
}

int main() {
    std::pair<int, int> start = {0, 5};
    std::pair<int, int> target = {9, 5};
    std::vector<int> map_locations = {
        1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
        1, 0, 0, 0, 0, 0, 0, 1, 1, 1,
        1, 0, 1, 1, 1, 1, 1, 1, 1, 1,
        1, 0, 1, 0, 0, 0, 1, 1, 0, 1,
        1, 0, 1, 0, 1, 1, 1, 1, 0, 1,
        1, 1, 1, 0, 1, 1, 1, 1, 0, 1,
    };
    std::pair<int, int> map_dimensions = {10, 6};
    std::vector<int> out_path = {};
    const bool did_find_path = FindPath(
        start, target, map_locations, map_dimensions, out_path);
    
    if (did_find_path) {
        std::cout << "Path found: " << std::endl;
        for (const auto index : out_path) std:: cout << index << " ";
        std::cout << std::endl;
    } else {
        std::cout << "Not path found." << std::endl;
    }
    
     // Testing solution print.
     /*for (int i = 0; i < map_dimensions.second; ++i) { // row
        for (int j = 0; j < map_dimensions.first; ++j) { // col
            const auto index = i * map_dimensions.first + j;
            if (std::find(out_path.begin(),
                          out_path.end(), index) != out_path.end()) {
                std::cout << " x ";
            } else {
                std::cout << "   ";
            }
        }
        std::cout << std::endl;
    }*/
    
    return 0;
}
