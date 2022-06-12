
#include <vector>
#include <memory>

// Aditional libraries for test example.
#include <thread>
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

// The original code should be implemented a main method.
// This was implemented just for show the multi-thread example usage.
// The code bellow isn't part of the test.

void PrintPath(std::pair<int, int> map_dimensions, std::vector<int> out_path) {
    std::cout << std::endl;
    
    int i = 0;
    for (int row = 0; row < map_dimensions.second; ++row) {
        for (int column = 0; column < map_dimensions.first; ++column) {
            const bool is_path_solution = std::find(
                out_path.begin(), out_path.end(), i) != out_path.end();
            std::cout << (is_path_solution ? "x" : "-");
            ++i;
        }
        std::cout << std::endl;
    }
}

int main() {
    std::pair<int, int> map_dimensions = {4, 3};
    std::vector<int> map_locations = {
        1, 1, 1, 1,
        0, 1, 0, 1,
        1, 1, 1, 1
    };
    std::pair<int, int> start_unit1 = {0, 0};
    std::pair<int, int> target_unit1 = {1, 2};
    std::vector<int> out_path_unit1 = {};
    
    std::pair<int, int> start_unit2 = {1, 1};
    std::pair<int, int> target_unit2 = {3, 1};
    std::vector<int> out_path_unit2 = {};
        
    std::thread t1(FindPath, start_unit1, target_unit1, std::ref(map_locations),
                   map_dimensions, std::ref(out_path_unit1));
    
    std::thread t2(FindPath, start_unit2, target_unit2, std::ref(map_locations),
                   map_dimensions, std::ref(out_path_unit2));
    
    t1.join();
    PrintPath(map_dimensions, out_path_unit1);
    t2.join();
    PrintPath(map_dimensions, out_path_unit2);
    
    return 0;
}
