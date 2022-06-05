#include <vector>
#include <utility>

// Where T is the object and C is the comparator.
template<typename T, typename C>
class BinaryHeap {
public:
    BinaryHeap();
    
    struct Comparator {
    public:
        int operator()(const T& left, const T& right) {
            return (left > right);
        }
    };
    
    T Top();
    void Push(T item);
    void Pop();
    
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
    
    std::size_t GetParentIndex(std::size_t index) const;
    std::size_t GetChildLeftIndex(std::size_t index) const;
    std::size_t GetChildRightIndex(std::size_t index) const;
};

template<typename T, typename C>
BinaryHeap<T, C>::BinaryHeap() : size_(0) {}

template<typename T, typename C>
T BinaryHeap<T, C>::Top() {
    return items_[0];
}

template<typename T, typename C>
void BinaryHeap<T, C>::Push(T item) {
    BinaryHeapItem heap_item{size_, item};
    items_.push_back(heap_item);
    ++size_;
    SortUp(heap_item);
}

template<typename T, typename C>
void BinaryHeap<T, C>::SortUp(BinaryHeap::BinaryHeapItem& item) {
    if (item.index == 0) return;
    
    auto i = item.index;
    while (i != 0 &&
           comparator(items_[GetParentIndex(i)].item, items_[i].item) > 0) {
        std::swap(items_[i], items_[GetParentIndex(i)]);
        i = GetParentIndex(i);
    }
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
        comparator(items_[l_index].item, items_[smallest_index].item) > 0) {
        smallest_index = l_index;
    }
    
    if (r_index < size_ &&
        comparator(items_[r_index].item, items_[smallest_index].item) > 0) {
        smallest_index = r_index;
    }
    
    if (smallest_index != item.index) {
        std::swap(items_[item.index], items_[smallest_index]);
        SortDown(items_[smallest_index]);
    }
}
