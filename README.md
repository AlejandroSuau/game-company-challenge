# Game Company Interview Challenge

_This is an API Challenge developed for a game company._

> "Every failed experiment is one step closer to success." - Denzel Washington.

## Used technologies.

* C++14.
* STL.

## Problem Description.

The problem which is trying to be solved here is to find the shortest path
between two points (coords). One is the start point and the other one is the
destination.

## Solution explanation.

The way it was solved was using A* algorithm which provides the shortest path
between two points. This algorithm was choosen because is an standard in the
industry refered as the 'best' to find the shortest path.

The way it works is by computing the movement costs to each neighbour (east,
west, north and south). This costs is calculated as a sum of 2 factors:
 - The distance from the node to the start node (called 'g').
 - The distance from the node to the target (called 'h').

 _Our movement 'weight' is 1 unit. In a terrain with different parts (mountains,
 water, etc.) it may vary. Is not the same crossing a mountain
 as crossing the grass._
 
 So the cost of a movement is called 'f' which is: f = g + h;
 
 Those distance are calculated using the "Manhattan distance heuristic" which
 allows you to calculate the distance from 2 points without diagonal movements:
 distance = abs(x1 - x2) + abs(y1 + y2)

## Restrictions.

* Time execution limit 7 seconds.
* Memory limit 1024 MB.
* Able to run in multi-thread environment.

## How to run.

_Go inside 'build' folder and the compile it with._

```
make -f Makefile
```

```
./game
```

It should output 2 path examples.

```
map_dimensions = {4, 3};
map_locations = {
    1, 1, 1, 1,
    0, 1, 0, 1,
    1, 1, 1, 1
};

start_unit1 = {0, 0};
target_unit1 = {1, 2};

-x--
-x--
-x--

start_unit2 = {1, 1};
target_unit2 = {3, 1};

-xxx
---x
----
```
