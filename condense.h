#include "graph.h"
//These functions expand on graph.h
#include "maze.h"

//doesn't do anything about cell coordinate values
//makes it real awkward when trying to read the printed maze and figure out the path taken
//leaves unconnected nodes which might be incompatible with current dijkstra implementation

//simplifies graph by removing unnecessary nodes from trees
void condense(Graph::vertex_descriptor start, Graph::vertex_descriptor end, Graph& g);

//sets all edge weights in graph to int w
void setEdgeWeights(Graph& g, int w);

//takes a graph and adds the path from end to start to a stack
bool graphToStack(Graph::vertex_descriptor start, Graph::vertex_descriptor end,
	std::stack<Graph::vertex_descriptor>& s, Graph& g);