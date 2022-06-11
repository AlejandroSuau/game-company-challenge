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
    
    std::vector<Node> nodes_;
    
    // Priority Queues doesn't allow to change the priority
    // so we needed to create a custom data structure: Binary heap.
    // This allows to update and insert with a complexity of O(log(N)).
    BinaryHeap nodes_open_;
    
    std::vector<Node*> GetNeighbours(const int index);
    
    void UpdateNodeNeighbours(Node* node);
    void UpdateNeighbourDataAndHeap(Node* neighbour);
    void ComputeOutPath(Node* last_node);
};
