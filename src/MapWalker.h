#pragma once

#include <memory>
#include <vector>

#include "Map.h"
#include "Heuristic.h"
#include "Node.h"
#include "BinaryHeap.h"


class MapWalker {
public:
    MapWalker(const Map& map,
              const Map::Cell start,
              const Map::Cell target,
              std::vector<int>& out_path,
              std::unique_ptr<IHeuristic> heuristic);
    
    bool FindPath();
    
private:
    const Map& map_;
    const int start_map_index_;
    const int target_map_index_;
    std::vector<int>& out_path_; // Start is not included but end is.
    std::unique_ptr<IHeuristic> heuristic_;
    
    std::vector<std::shared_ptr<Node>> nodes_;
    
    // Priority Queues doesn't allow to change the priority
    // so we needed to create a custom data structure: Binary heap.
    // This allows to update and insert with a complexity of O(log(N)).
    BinaryHeap nodes_open_;
    
    std::vector<std::shared_ptr<Node>> GetNeighbours(const int index) const;
    
    void UpdateNeighbourDataAndHeap(std::shared_ptr<Node> neighbour);
    void ComputeOutPath(std::shared_ptr<Node> last_node);
};
