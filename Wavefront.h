#pragma once

#include "maze.h"
#include "condense.h"

//assume equal edge weights
//return true if end is found, only finds single pair paths
//sets node weights as distance from start, with -1 as unexplored
bool pushWave(Graph::vertex_descriptor start, Graph::vertex_descriptor end, Graph& g);

//finds path after graph is marked by wavefront algorithm
//places nodes in a stack
void findPath(Graph::vertex_descriptor end, std::stack<Graph::vertex_descriptor>& s, Graph& g);


//optional print maze state weights function later

//part i
//reads name of maze file from keyboard
//Implement the Wavefront Algorithm to find single - pair paths in a given map.
void runWavefront();
