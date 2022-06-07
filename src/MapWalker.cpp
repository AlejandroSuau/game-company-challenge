#include "MapWalker.h"

#include <memory>
#include <algorithm>
#include <functional>


MapWalker::MapWalker(const Map& map,
                     const Map::Cell start,
                     const Map::Cell target,
                     std::vector<int>& out_path,
                     std::unique_ptr<IHeuristic> heuristic)
        : map_(map),
          start_map_index_(map.TranslateToOneBasedIndex(start)),
          target_map_index_(map.TranslateToOneBasedIndex(target)),
          out_path_(out_path),
          heuristic_(std::move(heuristic)) {
    const int nodes_size = static_cast<int>(map.GetLocations().size());
    for (int i = 0; i < nodes_size; ++i) {
        nodes_.push_back(std::make_shared<Node>(i));
    }
}

bool MapWalker::FindPath() {
    auto start_node = std::make_shared<Node>(start_map_index_);
    auto heap_index = nodes_open_.Push(start_node);
    start_node->is_open = true;
    start_node->heap_index = heap_index;
    
    while(nodes_open_.Size() > 0) {
        auto node = nodes_open_.Top();
        nodes_open_.Pop();
        node->is_closed = true;
        
        if (node->map_index == target_map_index_) {
            ComputeOutPath(node);
            return true;
        }
        
        const auto neighbours = GetNeighbours(node->map_index);
        for (auto neighbour : neighbours) {
            if (neighbour->is_closed) continue;
            
            const int g_cost = node->g + 1;
            if (!neighbour->is_open || g_cost < neighbour->g) {
                neighbour->g = g_cost;
                
                const auto dx_dy = map_.GetCoordAbsDifferencesBetweenIndexes(
                    neighbour->map_index, target_map_index_);
                const int dx = dx_dy.first;
                const int dy = dx_dy.second;
                neighbour->h = heuristic_->ComputeDistance(dx, dy);
                neighbour->f = neighbour->g + neighbour->h;
                
                neighbour->parent = node;
                std::size_t new_heap_index;
                if (neighbour->is_open) {
                    new_heap_index = nodes_open_.Update(
                        neighbour->heap_index, neighbour);
                } else {
                    new_heap_index = nodes_open_.Push(neighbour);
                    neighbour->is_open = true;
                }
                neighbour->heap_index = new_heap_index;
            }
        }
    }
    
    return false;
}

std::vector<std::shared_ptr<MapWalker::Node>> MapWalker::GetNeighbours(
        const int index) const {
    const auto dimensions = map_.GetDimensions();
    std::vector<int> neighbour_indexes = {
        index + 1, // E
        index - 1, // W
        index - dimensions.first, // N
        index + dimensions.first // S
    };
    
    std::vector<std::function<bool(int)>> is_valid_neighbour = {
        [&](const int i) { return (i % dimensions.first != 0); }, // E
        [&](const int i) { return ((i+1) % dimensions.first != 0); }, // W
        [&](const int i) { return (i >= 0); }, // N
        [&](const int i) { return (i < static_cast<int>(nodes_.size())); }, // S
    };
    
    // TODO: improvement, make the path look not ugly.
    // if (x + y) % 2 == 0: reverse both vectors to obtain: # S N W E
    
    std::vector<std::shared_ptr<Node>> neighbours;
    int neighbour_indexes_size = static_cast<int>(neighbour_indexes.size());
    for (int i = 0; i < neighbour_indexes_size; ++i) {
        const int neighbour_index = neighbour_indexes[i];
        if (is_valid_neighbour[i](neighbour_index) &&
                map_.IsTraversable(neighbour_index)) {
            neighbours.push_back(nodes_[neighbour_index]);
        }
    }
    
    return neighbours;
}

void MapWalker::ComputeOutPath(std::shared_ptr<Node> last_node) {
    if (last_node->parent == nullptr) return;
    
    while (last_node->parent != nullptr) {
        out_path_.push_back(last_node->map_index);
        last_node = last_node->parent;
    }
    std::reverse(out_path_.begin(), out_path_.end());
}
