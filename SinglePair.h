#pragma once
#include "maze.h"

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
//first calls findPathDFSStack to check if end is reachable from start to avoid looking deeper infinitely if not found.
bool findShortestPathDFS(Graph::vertex_descriptor start, Graph::vertex_descriptor end, Graph& g);

//helper function called by Iterative DFS
//runs DFS with stack up to depth parameter
bool limitedDFS(Graph::vertex_descriptor start, Graph::vertex_descriptor end, Graph& g, int limit);

//Runs BFS on graph g
//Inputs are the starting node and ending node(*(vEnd-1)) of graph g.
//if found, path can be traced using predecessors from end to start
bool findShortestPathBFS(Graph::vertex_descriptor start, Graph::vertex_descriptor end, Graph& g);

//takes a graph and adds the path from end to start to a stack
bool graphToStack(Graph::vertex_descriptor start, Graph::vertex_descriptor end,
    std::stack<Graph::vertex_descriptor>& s, Graph& g);

/*

(b) Write a recursive function findPathDFSRecursive that looks for a path from the start cell to the goal
cell using depth-first search.
(c) Write a function findPathDFSStack that looks for a path from the start cell to the goal cell using
depth-first search, but using a stack and not recursion.
(d) Write a function findShortestPathDFS that finds a shortest path from the start cell to the goal cell
using depth-first search.
(e) Write a function findShortestPathBFS that finds a shortest path from the start cell to the goal cell
using breadth-first search.



For parts (b)-(e), The code you submit should read the name of maze file from the keyboard, and then
apply each functions to that maze, one after the other. If no path from the start to the goal exists, the
program should print, No path exists. If a solution exists, the solver should simulate the solution to each
maze by calling the maze::print() function after each move.

*/