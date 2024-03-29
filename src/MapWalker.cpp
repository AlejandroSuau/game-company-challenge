#include "MapWalker.h"

#include <memory>
#include <functional>
#include <algorithm>


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
    for (int i = 0; i < nodes_size; ++i)
        nodes_.push_back(Node(i));
}

bool MapWalker::FindPath() {
    auto& start_node = nodes_[start_map_index_];
    nodes_open_.Push(&start_node);
    start_node.is_open = true;
    
    while(nodes_open_.Size() > 0) {
        auto* node = nodes_open_.Top();
        nodes_open_.Pop();
        node->is_closed = true;
        
        if (node->map_index == target_map_index_) {
            ComputeOutPath(*node);
            return true;
        }
        
        UpdateNodeNeighbours(*node);
    }
    
    return false;
}

void MapWalker::UpdateNodeNeighbours(Node& node) {
    Neighbours neighbours = {nullptr, nullptr, nullptr, nullptr};
    FillIndexNeighbours(node.map_index, neighbours);
    for (auto* neighbour : neighbours) {
        if (neighbour == nullptr || neighbour->is_closed) continue;
        
        const int g_cost = node.g + 1;
        if (!neighbour->is_open || g_cost < neighbour->g) {
            neighbour->g = g_cost;
            neighbour->parent = &node;
            UpdateNeighbourDataAndHeap(*neighbour);
        }
    }
}

void MapWalker::FillIndexNeighbours(const int index, Neighbours& neighbours) {
    const auto dimensions = map_.GetDimensions();
    int e_index = index + 1;
    if ((e_index) % dimensions.first != 0 && map_.IsTraversable(e_index))
        neighbours[0] = &nodes_[e_index];
    
    const int w_index = index - 1;
    if (index % dimensions.first != 0 && map_.IsTraversable(w_index))
        neighbours[1] = &nodes_[w_index];
    
    const int n_index = index - dimensions.first;
    if (n_index >= 0 && map_.IsTraversable(n_index))
        neighbours[2] = &nodes_[n_index];
    
    const int s_index = index + dimensions.first;
    if (s_index < static_cast<int>(nodes_.size()) && map_.IsTraversable(s_index))
        neighbours[3] = &nodes_[s_index];
}

void MapWalker::UpdateNeighbourDataAndHeap(Node& neighbour) {
    const auto dx_dy = map_.GetCoordAbsDifferencesBetweenIndexes(
        neighbour.map_index, target_map_index_);
    const int h = heuristic_->ComputeDistance(dx_dy.first, dx_dy.second);
    const int f = neighbour.g + h;
    
    neighbour.h = h;
    if (!neighbour.is_open) {
        neighbour.f = f;
        neighbour.is_open = true;
        nodes_open_.Push(&neighbour);
    } else {
        const bool sort_up = (f < neighbour.f);
        neighbour.f = f;
        nodes_open_.Update(neighbour.heap_index, sort_up);
    }
}

void MapWalker::ComputeOutPath(Node& last_node) {
    if (last_node.parent == nullptr) return;
    
    while (last_node.parent != nullptr) {
        out_path_.push_back(last_node.map_index);
        last_node = *last_node.parent;
    }
    
    std::reverse(out_path_.begin(), out_path_.end());
}
