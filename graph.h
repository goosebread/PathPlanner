#pragma once

// contains structs and typedefs from the original provided main file
#include <boost/graph/adjacency_list.hpp>

using namespace boost;
using namespace std;

struct VertexProperties;
struct EdgeProperties;

//changed from bidirectionalS to undirectedS. directional edges are not necessary
typedef adjacency_list<vecS, vecS, undirectedS, VertexProperties, EdgeProperties> Graph;

struct VertexProperties
{
    pair<int, int> cell; // maze cell (x,y) value
    Graph::vertex_descriptor pred; // predecessor node
    int weight;
    bool visited;
    bool marked;
};

// Create a struct to hold properties for each edge
struct EdgeProperties
{
    int weight;
    bool visited;
    bool marked;
};


//a commented out line that came with the provided file
// typedef property<edge_weight_t, int> EdgeProperty;

//slightly more organized global functions
namespace graphFunctions {
    // Mark all nodes in g as not visited.
    void clearVisited(Graph& g);

    // Set all node weights to w.
    void setNodeWeights(Graph& g, int w);

    //Unmark all nodes
    void clearMarked(Graph& g);
}

// Output operator for the Graph class. Prints out all nodes and their
// properties, and all edges and their properties.
std::ostream& operator<<(std::ostream& ostr, const Graph& g);

