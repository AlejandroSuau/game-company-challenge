#pragma once

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
