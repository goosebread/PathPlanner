#include "graph.h"

//function definitions for the global graph functions declared in graph.h

// Mark all nodes in g as not visited.
void graphFunctions::clearVisited(Graph& g) {

    Graph::vertex_iterator vIt, vEnd;
    tie(vIt, vEnd) = vertices(g);

    //loop through all vertices
    for (; vIt != vEnd; vIt++) {
        g[*vIt].visited = false;
    }
}

// Set all node weights to w.
void graphFunctions::setNodeWeights(Graph& g, int w) {
    Graph::vertex_iterator vIt, vEnd;
    tie(vIt, vEnd) = vertices(g);

    //loop through all vertices
    for (; vIt != vEnd; vIt++) {
        g[*vIt].weight = w;
    }
}

//Unmark all nodes
void graphFunctions::clearMarked(Graph& g) {
    Graph::vertex_iterator vIt, vEnd;
    tie(vIt, vEnd) = vertices(g);

    //loop through all vertices
    for (; vIt != vEnd; vIt++) {
        g[*vIt].marked = false;
    }
}

// Output operator for the Graph class. Prints out all nodes and their
// properties, and all edges and their properties.
std::ostream& operator<<(std::ostream& ostr, const Graph& g) {

    //nodes first
    Graph::vertex_iterator vIt, vEnd;
    tie(vIt, vEnd) = vertices(g);
    for (; vIt != vEnd; vIt++) {
        ostr << "Node " << *vIt << "\n";
        ostr << "\t cell: (" << g[*vIt].cell.first << ", " << g[*vIt].cell.second << ")\n";
        ostr << "\t pred: " << g[*vIt].pred << "\n";
        ostr << "\t weight: " << g[*vIt].weight << "\n";
        ostr << "\t visited: " << g[*vIt].visited << "\n";
        ostr << "\t marked: " << g[*vIt].marked << "\n";
    }

    //edges
    Graph::edge_iterator eIt, eEnd;
    tie(eIt, eEnd) = edges(g);
    for (; eIt != eEnd; eIt++) {
        ostr << "Edge " << *eIt << "\n";

        //should I include target and source. Node number or coordinates?
        //ostr << "\t target: (" << g[target(*eIt, g)].cell.first << ", " << g[target(*eIt, g)].cell.second << ")\n";
        //ostr << "\t source: (" << g[source(*eIt, g)].cell.first << ", " << g[source(*eIt, g)].cell.second << ")\n";

        //ostr << "\t target: " << target(*eIt, g) << "\n";
        //ostr << "\t source: " << source(*eIt, g) << "\n";

        ostr << "\t weight: " << g[*eIt].weight << "\n";
        ostr << "\t visited: " << g[*eIt].visited << "\n";
        ostr << "\t marked: " << g[*eIt].marked << "\n";
    }

    return ostr;
}

