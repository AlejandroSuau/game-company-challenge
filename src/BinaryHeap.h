#pragma once

#include <memory>
#include <vector>

#include "Node.h"


// Custom Binary Heap for A* Algorithm.
// TODO: Create a generic one, where T is the element and C is
// the comparator.
// template<class T, class C>
class BinaryHeap {
public:
    BinaryHeap();
    
    void Push(Node* item);
    void Update(std::size_t index, bool sort_up);
    Node* Top();
    void Pop();
    std::size_t Size() const;
    
private:
    struct BinaryHeapItem {
        std::size_t index;
        Node* item;
    };
    
    Node::Comparator comparator;
    std::vector<BinaryHeapItem> items_;
    std::size_t size_;
    
    void SortUp(BinaryHeapItem& item);
    void SortDown(BinaryHeapItem& item);
    void Swap(BinaryHeapItem& item_l, BinaryHeapItem& item_r);
    
    std::size_t GetParentIndex(std::size_t index) const;
    std::size_t GetChildLeftIndex(std::size_t index) const;
    std::size_t GetChildRightIndex(std::size_t index) const;
};
