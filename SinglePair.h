#pragma once
#include "maze.h"
#include "condense.h"

//simulates DFS with backtracking. prints the maze at each step. Uses recursion
//Inputs are the starting node and ending node(*(vEnd-1)) of graph g. maze m is used to print
bool findPathDFSRecursive(Graph::vertex_descriptor start, Graph::vertex_descriptor end, maze &m, Graph& g);

//Runs DFS with a stack on graph g
//Inputs are the starting node and ending node(*(vEnd-1)) of graph g.
//if found, path can be traced using predecessors from end to start
bool findPathDFSStack(Graph::vertex_descriptor start, Graph::vertex_descriptor end, Graph& g);

//Runs Iterative DFS on graph g to find shortest path
//Inputs are the starting node and ending node(*(vEnd-1)) of graph g.
//if found, path can be traced using predecessors from end to start
//first calls findPathDFSStack to check if end is reachable from start to avoid no termination
bool findShortestPathDFS(Graph::vertex_descriptor start, Graph::vertex_descriptor end, Graph& g);

//helper function called by Iterative DFS
//runs DFS recursively with a depth limit
bool limitedDFS(Graph::vertex_descriptor start, Graph::vertex_descriptor end, Graph& g, int limit);

//Runs BFS on graph g to find the shortest path
//Inputs are the starting node and ending node(*(vEnd-1)) of graph g.
//if found, path can be traced using predecessors from end to start
bool findShortestPathBFS(Graph::vertex_descriptor start, Graph::vertex_descriptor end, Graph& g);

//parts b-e
//reads name of maze file from keyboard
//applies each function to the maze one after another
void runBasic();
