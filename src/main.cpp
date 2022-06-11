
#include <vector>
#include <memory>

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
