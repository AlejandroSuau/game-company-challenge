#pragma once

#include <memory>
#include <vector>

#include "Map.h"
#include "Heuristic.h"
#include "BinaryHeap.h"


class MapWalker {
public:
    struct Node {
        int map_index;
        std::size_t heap_index;
        int g, h, f;
        bool is_open, is_closed;
        std::shared_ptr<Node> parent;
        
        Node(int index)
            : map_index(index), g(0), f(0), is_open(false), is_closed(false) {}
        
        struct Comparator {
        public:
            int operator()(const std::shared_ptr<Node> n1,
                           const std::shared_ptr<Node> n2) {
                return (n1->f > n2->f);
            }
        };
    };
    
    MapWalker(const Map& map,
              const Map::Cell start,
              const Map::Cell target,
              std::unique_ptr<IHeuristic> heuristic);
    
    bool FindPath();
    
//private:
    const Map& map_;
    const int start_map_index_;
    const int target_map_index_;
    std::unique_ptr<IHeuristic> heuristic_;
    std::vector<int> out_path_; // Start is not included but end is.
    
    std::vector<std::shared_ptr<Node>> nodes_;
    
    // Priority Queues doesn't allow to change the priority
    // so we needed to create a custom data structure: Binary heap.
    // This allows to update and insert with a complexity of O(log(N)).
    BinaryHeap<std::shared_ptr<Node>, Node::Comparator> nodes_open_;
    
    std::vector<std::shared_ptr<Node>> GetNeighbours(const int index) const;
    void UpdateNodeCost(std::shared_ptr<Node> node);
    
    void ComputeOutPath(std::shared_ptr<Node> last_node);
};
