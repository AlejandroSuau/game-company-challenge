#pragma once

#include <vector>
#include <utility>
#include <functional>


// Where T is the object and C is the comparator.
template<typename T, typename C>
class BinaryHeap {
public:
    BinaryHeap();
    
    /*struct Comparator {
    public:
        int operator()(const T& left, const T& right) {
            return (left > right);
        }
    };*/
    
    // Both methods Push and Update return the index in the heap.
    std::size_t Push(T item);
    std::size_t Update(std::size_t index, T new_item);
    T Top();
    void Pop();
    std::size_t Size() const;
    
private:
    struct BinaryHeapItem {
        std::size_t index;
        T item;
    };
    
    C comparator;
    std::vector<BinaryHeapItem> items_;
    std::size_t size_;
    
    void SortUp(BinaryHeapItem& item);
    void SortDown(BinaryHeapItem& item);
    void Swap(BinaryHeapItem& item_l, BinaryHeapItem& item_r);
    
    std::size_t GetParentIndex(std::size_t index) const;
    std::size_t GetChildLeftIndex(std::size_t index) const;
    std::size_t GetChildRightIndex(std::size_t index) const;
};

template<typename T, typename C>
BinaryHeap<T, C>::BinaryHeap() : size_(0) {}

template<typename T, typename C>
T BinaryHeap<T, C>::Top() {
    return items_[0].item;
}

template<typename T, typename C>
std::size_t BinaryHeap<T, C>::Push(T item) {
    BinaryHeapItem heap_item{size_, item};
    items_.push_back(heap_item);
    ++size_;
    SortUp(heap_item);
    
    return heap_item.index;
}

template<typename T, typename C>
void BinaryHeap<T, C>::SortUp(BinaryHeap::BinaryHeapItem& item) {
    auto i = item.index;
    while (i != 0 &&
           comparator(items_[GetParentIndex(i)].item, items_[i].item) > 0) {
        Swap(items_[i], items_[GetParentIndex(i)]);
        i = GetParentIndex(i);
    }
}

template<typename T, typename C>
void BinaryHeap<T, C>::Swap(BinaryHeapItem& item_l, BinaryHeapItem& item_r) {
    std::swap(item_l, item_r);
    const auto item_l_index = item_l.index;
    item_l.index = item_r.index;
    item_r.index = item_l_index;
}

template<typename T, typename C>
std::size_t BinaryHeap<T, C>::Update(std::size_t index, T new_item) {
    std::function<void(BinaryHeapItem& item)> sort_algorithm;
    using namespace std::placeholders;
    if (comparator(items_[index].item, new_item) > 0) {
        sort_algorithm = std::bind(&BinaryHeap::SortUp, this, _1);
    } else {
        sort_algorithm = std::bind(&BinaryHeap::SortDown, this, _1);
    }
    
    items_[index].index = index;
    items_[index].item = new_item;
    sort_algorithm(items_[index]);
    
    return items_[index].index;
}

template<typename T, typename C>
std::size_t BinaryHeap<T, C>::GetParentIndex(std::size_t index) const {
    return ((index - 1) / 2);
}

template<typename T, typename C>
std::size_t BinaryHeap<T, C>::GetChildLeftIndex(std::size_t index) const {
    return (2 * index + 1);
}

template<typename T, typename C>
std::size_t BinaryHeap<T, C>::GetChildRightIndex(std::size_t index) const {
    return (2 * index + 2);
}

template<typename T, typename C>
void BinaryHeap<T, C>::Pop() {
    --size_;
    items_[0] = items_[size_];
    items_[0].index = 0;
    items_.pop_back();
    SortDown(items_[0]);
}

template<typename T, typename C>
void BinaryHeap<T, C>::SortDown(BinaryHeapItem& item) {
    const auto l_index = GetChildLeftIndex(item.index);
    const auto r_index = GetChildRightIndex(item.index);
    auto smallest_index = item.index;
    if (l_index < size_ &&
        comparator(items_[l_index].item, items_[smallest_index].item) == 0) {
        smallest_index = l_index;
    }
    
    if (r_index < size_ &&
        comparator(items_[r_index].item, items_[smallest_index].item) == 0) {
        smallest_index = r_index;
    }
    
    if (smallest_index != item.index) {
        Swap(items_[item.index], items_[smallest_index]);
        SortDown(items_[smallest_index]);
    }
}

template<typename T, typename C>
std::size_t BinaryHeap<T, C>::Size() const {
    return size_;
}
