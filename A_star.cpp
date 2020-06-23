#include "A_star.h"

bool aStar(Graph::vertex_descriptor start, Graph::vertex_descriptor end, Graph& g) {
    graphFunctions::clearMarked(g);
    graphFunctions::clearVisited(g);

    //initialize min priority queue
    heapV<Graph::vertex_descriptor, Graph> frontier;
    g[start].marked = true;
    std::pair<int, int> endCoordinates = g[end].cell;
    g[start].weight = estimateDistance(g[start].cell, endCoordinates);
    frontier.minHeapInsert(start, g);

    while (frontier.size() != 0) {

        //get node
        Graph::vertex_descriptor currentNode = frontier.extractMinHeapMinimum(g);
        g[currentNode].visited = true;

        //stop if this is the end
        if (currentNode == end) { return true; }

        //change to weight from start
        g[currentNode].weight -= estimateDistance(g[currentNode].cell, endCoordinates);

        //add neighbors to stack
        Graph::adjacency_iterator nIt, nEnd;
        boost::tie(nIt, nEnd) = adjacent_vertices(currentNode, g);

        for (; nIt != nEnd; nIt++) {

            //if not visited
            if (!g[*nIt].visited) {

                //i don't know if this will actually happen
                //it shouldn't if the algorithm was implemented properly...
                if (g[*nIt].marked) {

                    int newWeight = g[currentNode].weight + g[edge(currentNode, *nIt, g).first].weight
                        + estimateDistance(g[*nIt].cell, endCoordinates);
                    //if cheaper
                    if (newWeight < g[*nIt].weight) {
                        //update node path
                        g[*nIt].pred = currentNode;
                        g[*nIt].weight = newWeight;

                        Graph::vertex_descriptor key = *nIt;
                        frontier.minHeapDecreaseKey(frontier.getIndex(key), g);
                    }
                }
                else {
                    //add node to frontier
                    g[*nIt].pred = currentNode;
                    g[*nIt].marked = true;
                    g[*nIt].weight = g[currentNode].weight + g[edge(currentNode, *nIt, g).first].weight
                        + estimateDistance(g[*nIt].cell, endCoordinates);

                    frontier.minHeapInsert(*nIt, g);
                }
            }
        }
    }
    //end not found
    return false;
}

int estimateDistance(std::pair<int, int>start, std::pair<int, int> end) {
    return(std::abs(start.first - end.first) + std::abs(start.second - end.second));
}

void runAStar(){
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

    boost::tie(vIt, vEnd) = vertices(g);
    //vEnd is a sentinel value, can't dereference

    std::cout << "A-star:\n";

    setEdgeWeights(g, 1);
    //condense(*vIt, *(vEnd - 1), g);

    if (aStar(*vIt, *(vEnd - 1), g)) {
        std::stack<Graph::vertex_descriptor> s;
        graphToStack(*vIt, *(vEnd - 1), s, g);
        m.printPath(*(vEnd - 1), s, g);

        //cout << g;
    }
    else {
        std::cout << "No path exists\n";
    }
}
