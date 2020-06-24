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

// Relaxes the edge e.
void relax(Graph &g, Graph::edge_descriptor e){
    int s_weight = g[boost::source(e,g)].weight;
    int t_weight = g[boost::target(e,g)].weight;
    int e_weight = g[e].weight;
    if(s_weight > t_weight+e_weight){
        g[boost::source(e,g)].weight = g[boost::target(e,g)].weight+e_weight;
        g[boost::source(e,g)].pred = boost::target(e,g);
    }
    else if(t_weight > s_weight+e_weight){
        g[boost::target(e,g)].weight = s_weight+e_weight;
        g[boost::target(e,g)].pred = boost::source(e,g);
    }
}

// Uses Dijsktra's algorithm to search for a shortest path from node s to every node in g, where all node weights must be positive.
// If a path exists to every node, returns true and returns false otherwise.
bool dijkstra(Graph &g, Graph::vertex_descriptor s){
    graphFunctions::clearVisited(g);
    graphFunctions::clearMarked(g);
    graphFunctions::setNodeWeights(g,999999999); // initialize nodes
    g[s].weight = 0; // initialize starting node
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
    graphFunctions::clearVisited(g);
    graphFunctions::setNodeWeights(g,999999999); // initialize nodes
    g[s].weight = 0; // initialize starting node
    Graph::edge_iterator eIt, eEnd;
    for(int i = 1; i < boost::num_vertices(g); i++){
        std::tie(eIt, eEnd) = edges(g);
        for(; eIt != eEnd; eIt++){
            // set each node's pred field to the predecessor node in a shortest path from node s, if such a path exists
            // the weight property of nodes is used to store the shortest path estimates
            relax(g,*eIt);
        }
    }
    std::tie(eIt, eEnd) = edges(g);
    for(; eIt != eEnd; eIt++){
        if(g[boost::target(*eIt,g)].weight > g[boost::source(*eIt,g)].weight+g[*eIt].weight){
            return false; // returns false if a negative cycle is reachable from s
        }
    }
    return true; // returns true if a negative cycle is not reachable from s
}

void runBFDijkstra() {
    ifstream fin;

    // Read the maze from the file.
    //ask for keyboard input here
    std::cout << "Enter the file name for the maze:\n";
    string fileName;// = "maze_test.txt";
    std::getline(std::cin, fileName);

    //test file validity
    fin.open(fileName.c_str());
    if (!fin) {
        cerr << "Cannot open " << fileName << endl;
        exit(1);
    }

    maze m(fin);
    fin.close();

    Graph g;
    m.mapMazeToGraph(g);

    Graph::vertex_iterator vIt, vEnd;

    graphFunctions::clearMarked(g);
    graphFunctions::clearVisited(g);
    graphFunctions::setNodeWeights(g, 1);
    setEdgeWeights(g, 1);

    boost::tie(vIt, vEnd) = vertices(g);

    std::cout << "Bellman-Ford:\n";
    if (bellmanFord(g, *vIt)) {
        std::stack<Graph::vertex_descriptor> s;
        graphToStack(*vIt, *(vEnd - 1), s, g);
        m.printPath(*(vEnd - 1), s, g);
    }
    else {
        std::cout << "No path exists\n";
    }

    std::cout << "Dijkstra:\n";
    if (dijkstra(g, *vIt)) {
        std::stack<Graph::vertex_descriptor> s;
        graphToStack(*vIt, *(vEnd - 1), s, g);
        m.printPath(*(vEnd - 1), s, g);
    }
    else {
        std::cout << "No path exists\n";
    }
}