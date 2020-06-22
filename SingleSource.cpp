#include "SingleSource.h"
#include "heapV.h"

// Relaxes the edge from node u to v.
void relax(Graph &g, Graph::vertex_descriptor u, Graph::vertex_descriptor v){
    std::pair<Graph::edge_descriptor, bool> checkEdge = boost::edge(u,v,g);
    if(checkEdge.second){
        if(g[v].weight > g[u].weight+g[checkEdge.first].weight){
            g[v].weight = g[u].weight+g[checkEdge.first].weight;
            g[v].pred = u;
        }
    }
}

// Uses Dijsktra's algorithm to search for a shortest path from node s to every node in g, where all node weights must be positive.
// If a path exists to every node, returns true and returns false otherwise.
bool dijkstra(Graph &g, Graph::vertex_descriptor s){
    graphFunctions::clearVisited(g);
    graphFunctions::clearMarked(g);
    graphFunctions::setNodeWeights(g,999999999); // initialize nodes
    g[s].weight = 0; // initialize statring node
    heapV<Graph::vertex_descriptor, Graph> vertex_heap; // a min-heap is used to store the nodes and find the one with the smallest value
    Graph::vertex_iterator vIt, vEnd;
    std::tie(vIt, vEnd) = vertices(g);
    std::vector<Graph::vertex_descriptor> vertex_vector(1,s);
    int found_nodes = 1; // keeps track of how many nodes have been found
    vertex_heap.initializeMinHeap(vertex_vector,g);
    while(vertex_heap.size() > 0){
        Graph::vertex_descriptor u = vertex_heap.extractMinHeapMinimum(g); // extract minimum vertex from heap
        g[u].visited = true;
        Graph::adjacency_iterator aIt, aEnd;
        std::tie(aIt, aEnd) = adjacent_vertices(u,g);
        for(; aIt != aEnd; aIt++){
            Graph::vertex_descriptor adj_vert = *aIt;
            if(!g[adj_vert].visited){
                if(!g[adj_vert].marked){
                    g[adj_vert].marked = true;
                    found_nodes++;
                }
                vertex_heap.minHeapInsert(adj_vert,g); // add adjacent vertex to the heap
                // set each node's pred field to the predecessor node in a shortest path from node s, if such a path exists
                // the weight property of nodes is used to store the shortest path estimates
                relax(g,u,adj_vert);
                vertex_heap.minHeapDecreaseKey(vertex_heap.getIndex(adj_vert),g); // assumes the value decreased for vert, rebuilds the min-heap
            }
        }
    }
    if(found_nodes == boost::num_vertices(g)){return true;} // if a path exists to every node, returns true
    return false; // if there isn't a path to every node, returns false
}

// Uses the Bellman-Ford algorithm to search for a shortest path from node s to every node in graph g, where g can have negative edge weights.
bool bellmanFord(Graph& g, Graph::vertex_descriptor s){
    graphFunctions::clearVisited(g);
    graphFunctions::setNodeWeights(g,999999999); // initialize nodes
    g[s].weight = 0; // initialize statring node
    Graph::edge_iterator eIt, eEnd;
    for(int i = 1; i < boost::num_vertices(g); i++){
        std::tie(eIt, eEnd) = edges(g);
        for(; eIt != eEnd; eIt++){
            // set each node's pred field to the predecessor node in a shortest path from node s, if such a path exists
            // the weight property of nodes is used to store the shortest path estimates
            relax(g,boost::source(*eIt,g),boost::target(*eIt,g));
            relax(g,boost::target(*eIt,g),boost::source(*eIt,g));
        }
    }
    std::tie(eIt, eEnd) = edges(g);
    for(; eIt != eEnd; eIt++){
        if(g[boost::target(*eIt,g)].weight > g[boost::source(*eIt,g)].weight+g[*eIt].weight){
            return false; // returns false if a negative cycle is reachable from s
        }
    }
    return true;// returns true if a negative cycle is not reachable from s
}