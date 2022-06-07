#include "Map.h"

#include <cmath>


Map::Map(const std::pair<int, int> dimensions, std::vector<int> locations)
    : dimensions_(dimensions), locations_(std::move(locations)) {}

int Map::TranslateToOneBasedIndex(const Cell cell) const {
    return (cell.row * dimensions_.first + cell.column);
}

Map::Cell Map::TranslateToCell(const int index) const {
    int column = index % dimensions_.first;
    int row = std::floor(index / dimensions_.first);
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

const std::pair<int, int> Map::GetDimensions() const {
    return dimensions_;
}

const std::vector<int>& Map::GetLocations() const {
    return locations_;
}
