#pragma once

#include "maze.h"

// Relaxes the edge from node u to v.
void relax(Graph &g, Graph::vertex_descriptor u, Graph::vertex_descriptor v);

// Uses Dijsktra's algorithm to search for a shortest path from node s to every node in g, where all node weights must be positive.
// If a path exists to every node, returns true and returns false otherwise.
bool dijkstra(Graph &g, Graph::vertex_descriptor s);

// Uses the Bellman-Ford algorithm to search for a shortest path from node s to every node in graph g, where g can have negative edge weights.
// Returns false if a negative cycle is reachable from s and returns true otherwise.
bool bellmanFord(Graph &g, Graph::vertex_descriptor s);