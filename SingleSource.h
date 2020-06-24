#pragma once

#include "maze.h"
#include "condense.h"
#include "heapV.h"

// Relaxes the edge from node u to v. Used in dijkstra.
void relax(Graph &g, Graph::vertex_descriptor u, Graph::vertex_descriptor v);

// Relaxes the edge e. Used in bellmanFord.
void relax(Graph &g, Graph::edge_descriptor e);

// Uses Dijsktra's algorithm to search for a shortest path from node s to every node in g, where all node weights must be positive.
// If a path exists to every node, returns true and returns false otherwise.
bool dijkstra(Graph &g, Graph::vertex_descriptor s);

// Uses the Bellman-Ford algorithm to search for a shortest path from node s to every node in graph g, where g can have negative edge weights.
// Returns false if a negative cycle is reachable from s and returns true otherwise.
bool bellmanFord(Graph &g, Graph::vertex_descriptor s);

//parts g-h
//reads name of maze file from keyboard
//runs bellman ford and dijkstra
void runBFDijkstra();