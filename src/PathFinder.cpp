#include "PathFinder.h"

#include <memory>
#include <algorithm>
#include <iostream>


PathFinder::PathFinder(const Map& map,
                     const Map::Cell start,
                     const Map::Cell target,
                     std::unique_ptr<IHeuristic> heuristic)
    : map_(map),
      start_map_index_(map.TranslateToOneBasedIndex(start)),
      target_map_index_(map.TranslateToOneBasedIndex(target)),
      heuristic_(std::move(heuristic)),
      out_path_{} {}

bool PathFinder::FindPath() {
    // 1. Add the start node to open.
    auto start_node = std::make_shared<Node>(start_map_index_);
    nodes_open_.push_back(start_node);
    start_node->is_open = true;
    
    // 2. Loop.
    while(nodes_open_.size() > 0) {
        // 3. Pop the lowest f.
        ///////
        auto lowest_it = nodes_open_.begin();
        std::shared_ptr<Node> node = *nodes_open_.begin();
        for (auto it = nodes_open_.begin(); it != nodes_open_.end(); ++it) {
            if ((*it)->f < node->f) {
                lowest_it = it;
                node = *it;
            }
        }
        nodes_open_.erase(lowest_it);
        
        ///////
        //auto node = nodes_open_.top();
        //nodes_open_.pop();
        node->is_closed = true;
        
        // 6. If current is the target, then path has been found.
        if (node->map_index == target_map_index_) {
            ComputeOutPath(node);
            return true;
        }
        
        // 7. For each neighbour of the current node.
        const auto neighbours = map_.GetNeighbours(node->map_index);
        for (const auto neighbour_index : neighbours) {
            auto neighbour = std::make_shared<Node>(neighbour_index);
            if (neighbour->is_closed) continue;
            
            // Distance to the starting node.
            const int g_cost = node->g + 1;
            if (!neighbour->is_open || g_cost < neighbour->g) {
                neighbour->g = g_cost;
                
                const auto dx_dy = map_.GetCoordAbsDifferencesBetweenIndexes(
                    neighbour-> map_index, target_map_index_);
                const int dx = dx_dy.first;
                const int dy = dx_dy.second;
                neighbour->h = heuristic_->ComputeDistance(dx, dy);
                
                neighbour->parent = node;
                if (!neighbour->is_open) {
                    nodes_open_.push_back(neighbour);
                    neighbour->is_open = true;
                } else {
                    // binary heap for example. O(log(n))
                    // neighbour updated. // pop and insert again.
                }
            }
            
            
            
            
            // 8. If neighbour is not traversable or is in closed, continue.
            /*if (!map_.IsTraversable(neighbour_index) ||
                IsIndexIn(neighbour_index, nodes_closed_)) continue;
            
            auto neighbour = std::make_shared<Node>(neighbour_index);
            // 9. If distance from current to neighbour is shorter
            //    or neighbour is not in open.
            
            const int current_g = current->g + 1;
            const bool neighbour_is_open = IsIndexIn(neighbour_index, nodes_open_);
            if (current_g > current->f || !neighbour_is_open) {
                current->g = current_g;
                
                const auto dx_dy = map_.GetCoordAbsDifferencesBetweenIndexes(
                    current-> map_index, neighbour_index);
                const int dx = dx_dy.first;
                const int dy = dx_dy.second;
                current->h = current->h || heuristic_->ComputeDistance(dx, dy);
                // 10. Set f cost of neighbour.
                current->f = current->g + current->h;
                // 11. Set parent of neighbour to current.
                neighbour->parent = current;
                if (!neighbour_is_open) nodes_open_.push_back(neighbour);*/
        }
    }
    
    return false;
}

void PathFinder::ComputeOutPath(std::shared_ptr<Node> last_node) {
    if (last_node->parent == nullptr) return;
    
    while (last_node->parent != nullptr) {
        out_path_.push_back(last_node->map_index);
        last_node = last_node->parent;
    }
    std::reverse(out_path_.begin(), out_path_.end());
}
