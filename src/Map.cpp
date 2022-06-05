#include "Map.h"

#include <cmath>


Map::Map(const std::pair<int, int> dimensions, std::vector<int> locations)
    : dimensions_(dimensions), locations_(std::move(locations)) {}

int Map::TranslateToOneBasedIndex(const Cell cell) const {
    return (cell.row * dimensions_.first + cell.column);
}

Map::Cell Map::TranslateToCell(const int index) const {
    int column = index % dimensions_.first;
    int row = std::floor(index / dimensions_.second);
    return Cell{column, row};
}

bool Map::IsTraversable(const int index) const {
    return locations_[index];
}

std::pair<int, int> Map::GetCoordAbsDifferencesBetweenIndexes(
        const int index_a, const int index_b) const {
    const Cell a = TranslateToCell(index_a);
    const Cell b = TranslateToCell(index_b);
    return std::make_pair(abs(b.column - a.column), abs(b.row - a.row));
}

std::vector<int> Map::GetNeighbours(const int index) const {
    std::vector<std::function<bool(int)>> is_valid_neighbour = {
        [&](const int i) { return (i >= 0); }, // t
        [&](const int i) { return (i % (dimensions_.second - 1) > 0); }, // r
        [&](const int i) { return (i < locations_.size()); }, // b
        [&](const int i) { return ((i+1) % (dimensions_.first) > 0); }, // l
    };
    
    std::vector<int> neighbour_indexes = {
        index - dimensions_.first,
        index + 1,
        index - 1,
        index + dimensions_.first
    };
    
    std::vector<int> neighbours;
    for (std::size_t i = 0; i < neighbour_indexes.size(); ++i) {
        const int index = neighbour_indexes[i];
        if (is_valid_neighbour[i](index) && IsTraversable(index))
            neighbours.push_back(index);
    }
    
    return neighbours;
}

const std::pair<int, int> Map::GetDimensions() const {
    return dimensions_;
}

const std::vector<int>& Map::GetLocations() const {
    return locations_;
}
