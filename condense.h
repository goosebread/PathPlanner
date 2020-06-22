#include "maze.h"

//doesn't do anything about cell coordinate values
//makes it real awkward when trying to read the printed maze and figure out the path taken

void condense(Graph::vertex_descriptor start, Graph::vertex_descriptor end, Graph& g) {
	//find nodes with only 2 neighbors
	std::pair<Graph::vertex_iterator, Graph::vertex_iterator> vItrRange = vertices(g);
	for (Graph::vertex_iterator vItr = vItrRange.first; vItr != vItrRange.second; ++vItr) {

		//blacklist start and end vertices
		if (*vItr != start && *vItr != end) {

			int degree = out_degree(*vItr, g);
			if (degree == 2) {
				//join neighbors directly
				std::pair<Graph::adjacency_iterator, Graph::adjacency_iterator> neighbors = adjacent_vertices(*vItr, g);
				//neighbors.second is the sentinel value, hence the -1
				std::pair<Graph::edge_descriptor, bool> newEdge = add_edge(*neighbors.first, *(neighbors.second - 1), g);

				//update weight
				g[newEdge.first].weight = g[edge(*vItr, *neighbors.first, g).first].weight + g[edge(*vItr, *(neighbors.second - 1), g).first].weight;

				//remove old edges
				clear_vertex(*vItr, g);

				//remove_vertex(*vItr, g);

				//the vertex is no longer connected to the graph. 
				//it is left as extra overhead and not deleted using
				//remove_vertex since the vertices are stored as vectors (vecS) 
				//and not lists (listS). I don't have the time to poke around too much here
			}
		}
	}

	//remove the node and join the neighbors directly
	//update new edge weight
}


//probably belongs in graph.h
//lets call it an extension
void setEdgeWeights(Graph& g, int w){
	Graph::edge_iterator eIt, eEnd;
	tie(eIt, eEnd) = edges(g);

	//loop through all edges
	for (; eIt != eEnd; eIt++) {
		g[*eIt].weight = w;
	}
}