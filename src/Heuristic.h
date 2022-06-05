#pragma once

class IHeuristic {
public:
    virtual ~IHeuristic();
    virtual int ComputeDistance(const int dx, const int dy) = 0;
};

class Manhattan : public IHeuristic {
public:
    ~Manhattan();
    int ComputeDistance(const int dx, const int dy) override;
};


