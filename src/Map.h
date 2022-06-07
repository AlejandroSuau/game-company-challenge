#pragma once

#include <vector>


class Map {
public:
    struct Cell {
        int column;
        int row;
    };
    
    Map(const std::pair<int, int> dimensions, std::vector<int> locations);
    
    bool IsTraversable(const int index) const;
    
    int TranslateToOneBasedIndex(const Cell cell) const;
    Cell TranslateToCell(const int index) const;
    
    std::pair<int, int> GetCoordAbsDifferencesBetweenIndexes(
        const int index_a, const int index_b) const;
    const std::pair<int, int> GetDimensions() const;
    const std::vector<int>& GetLocations() const;
    
private:
    const std::pair<int, int> dimensions_; // <Width, Height>.
    const std::vector<int> locations_; // Traversable = 1; 0 Otherwise.
};
