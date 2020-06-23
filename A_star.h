#pragma once

#include "maze.h"
#include "heapV.h"
#include "condense.h"

//Runs A-star on graph g to find shortest path
//Inputs are the starting node and ending node(*(vEnd-1)) of graph g.
//if found returns true and path can be traced using predecessors from end to start
bool aStar(Graph::vertex_descriptor start, Graph::vertex_descriptor end, Graph& g);

//heuristic function. never overestimates actual distance
int estimateDistance(std::pair<int, int>start, std::pair<int, int> end);

//part j
//reads name of maze file from keyboard
//Implements A-star algorithm
void runAStar();