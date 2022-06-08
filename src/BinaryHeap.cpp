#include "BinaryHeap.h"


BinaryHeap::BinaryHeap() : size_(0) {}

std::shared_ptr<Node> BinaryHeap::Top() {
    return items_[0].item;
}

void BinaryHeap::Push(std::shared_ptr<Node> item) {
    BinaryHeapItem heap_item{size_, item};
    item->heap_index = size_;
    items_.push_back(heap_item);
    ++size_;
    SortUp(heap_item);
}

void BinaryHeap::SortUp(BinaryHeap::BinaryHeapItem& item) {
    auto i = item.index;
    while (i != 0 &&
           comparator(items_[GetParentIndex(i)].item, items_[i].item) > 0) {
        Swap(items_[i], items_[GetParentIndex(i)]);
        i = GetParentIndex(i);
    }
}

void BinaryHeap::Swap(BinaryHeapItem& item_l, BinaryHeapItem& item_r) {
    std::swap(item_l, item_r);
    const std::size_t item_l_index = item_l.index;
    item_l.index = item_r.index;
    item_l.item->heap_index = item_l.index;
    
    item_r.index = item_l_index;
    item_r.item->heap_index = item_r.index;
}

void BinaryHeap::Update(std::size_t index, bool sort_up) {
    if (sort_up) {
        SortUp(items_[index]);
    } else {
        SortDown(items_[index]);
    }
}

std::size_t BinaryHeap::GetParentIndex(std::size_t index) const {
    return ((index - 1) / 2);
}

std::size_t BinaryHeap::GetChildLeftIndex(std::size_t index) const {
    return (2 * index + 1);
}

std::size_t BinaryHeap::GetChildRightIndex(std::size_t index) const {
    return (2 * index + 2);
}

void BinaryHeap::Pop() {
    --size_;
    items_[0] = items_[size_];
    items_[0].index = 0;
    items_.pop_back();
    SortDown(items_[0]);
}

void BinaryHeap::SortDown(BinaryHeapItem& item) {
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

std::size_t BinaryHeap::Size() const {
    return size_;
}
