#include "Wavefront.h"

bool pushWave(Graph::vertex_descriptor start, Graph::vertex_descriptor end, Graph& g) {

    //weight of -1 indicates not visited
    graphFunctions::setNodeWeights(g, -1);

    //initialize
    g[start].weight = 0;
    std::queue<Graph::vertex_descriptor> wave;
    wave.push(start);

    //node weights are guaranteed to be visited in nondecreasing order
    while (!wave.empty()) {
        //get node
        Graph::vertex_descriptor currentNode = wave.front();
        wave.pop();

        //stop if this is the end
        if (currentNode == end) { return true; }

        //add neighbors to wave
        Graph::adjacency_iterator nIt, nEnd;
        boost::tie(nIt, nEnd) = adjacent_vertices(currentNode, g);

        int currentWeight = g[currentNode].weight;
        for (; nIt != nEnd; nIt++) {
            //only unexplored neighbors
            if (g[*nIt].weight == -1) {
                g[*nIt].weight = currentWeight + 1;
                wave.push(*nIt);
            }
        }
    }
    //end not found
    return false;
}

void findPath(Graph::vertex_descriptor end, std::stack<Graph::vertex_descriptor>& s, Graph& g) {

    Graph::vertex_descriptor currentNode = end;
    while (g[currentNode].weight != 0) {
        s.push(currentNode);

        //move to lower weight node
        Graph::adjacency_iterator nIt, nEnd;
        boost::tie(nIt, nEnd) = adjacent_vertices(currentNode, g);

        int currentWeight = g[currentNode].weight;
        for (; nIt != nEnd; nIt++) {
            if (g[*nIt].weight < currentWeight) {
                currentNode = *nIt;
                break;
            }
        }
    }
    //add start
    s.push(currentNode);
}

void runWavefront() {
    ifstream fin;

    // Read the maze from the file.
    //ask for keyboard input here
    string fileName = "maze_test.txt";

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
    boost::tie(vIt, vEnd) = vertices(g);
    //vEnd is a sentinel value, can't dereference

    std::cout << "Wavefront:\n";
    if (pushWave(*vIt, *(vEnd - 1), g)) {
        std::stack<Graph::vertex_descriptor> s;
        findPath(*(vEnd - 1), s, g);
        m.printPath(*(vEnd - 1), s, g);
    }
    else {
        std::cout << "No path exists\n";
    }
}
