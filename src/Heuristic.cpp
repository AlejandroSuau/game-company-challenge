#include "Heuristic.h"

IHeuristic::~IHeuristic() {}

Manhattan::~Manhattan() {}
int Manhattan::ComputeDistance(const int dx, const int dy) {
    return (dx + dy);
}
