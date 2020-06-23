#include "SinglePair.h"

//makes a path through the predecessors of nodes and stores path in a stack
bool findPathDFSRecursive(Graph::vertex_descriptor start, Graph::vertex_descriptor end, maze &m, Graph& g){   
    //use clearVisited() and clearMarked() before calling DFS

    //visit this node
    m.print(g[end].cell.first, g[end].cell.second, g[start].cell.first, g[start].cell.second);

    //stop if this is the end
    if (start==end) { return true; }

    //check unexplored connected nodes
    Graph::adjacency_iterator nIt, nEnd;
    boost::tie(nIt, nEnd) = adjacent_vertices(start, g);

    g[start].marked = true;
    for (; nIt != nEnd; nIt++) {
        if (!g[*nIt].visited && !g[*nIt].marked) {
            //add to children
            g[*nIt].pred = start;
            //if found in child
            if (findPathDFSRecursive(*nIt, end, m, g)) {
                return true;
            }
            else {
                //backtrack to this node
                m.print(g[end].cell.first, g[end].cell.second, g[start].cell.first, g[start].cell.second);
            }
        }
    }
    g[start].visited = true;

    //if not found in children, the end is not accecible through this parent
    return false;
}

bool findPathDFSStack(Graph::vertex_descriptor start, Graph::vertex_descriptor end, Graph& g){
    graphFunctions::clearMarked(g);
    graphFunctions::clearVisited(g);

    //initialize
    std::stack<Graph::vertex_descriptor> frontier;
    frontier.push(start);

    while (!frontier.empty()) {
        //get node
        Graph::vertex_descriptor currentNode = frontier.top();
        frontier.pop();

        //visit node if not visited yet
        if (!g[currentNode].visited) {
            g[currentNode].visited = true;

            //stop if this is the end
            if (currentNode==end) { return true; }

            //add neighbors to stack
            Graph::adjacency_iterator nIt, nEnd;
            boost::tie(nIt, nEnd) = adjacent_vertices(currentNode, g);

            for (; nIt != nEnd; nIt++) {
                if (!g[*nIt].visited && !g[*nIt].marked) {
                    //add to stack
                    g[*nIt].pred = currentNode;
                    g[*nIt].marked = true;
                    frontier.push(*nIt);
                }
            }
        }
    }
    //end not found
    return false;
}

bool findShortestPathDFS(Graph::vertex_descriptor start, Graph::vertex_descriptor end, Graph& g){
    //check to make sure a path exists first
    if (!findPathDFSStack(start, end, g)) {
        return false;
    }
    //a path must exist
    else {
        graphFunctions::clearMarked(g);
        graphFunctions::clearVisited(g);

        int limit = 1;
        bool found = false;
        while (!found) {
            found = limitedDFS(start, end, g, limit);
            limit++;
        }
        return true;
    }
}

//start with limit = 1 and increase
//not as restrictive with checking visited nodes. the same node exists at multiple positions in the tree
bool limitedDFS(Graph::vertex_descriptor start, Graph::vertex_descriptor end, Graph& g, int limit){

    //stop if this is the end
    if (start == end) { return true; }

    //stop if limit is reached
    if (limit == 0) { return false; }

    //check connected nodes
    Graph::adjacency_iterator nIt, nEnd;
    boost::tie(nIt, nEnd) = adjacent_vertices(start, g);

    for (; nIt != nEnd; nIt++) {
        //don't loop back to parent
        if (*nIt!=g[start].pred){

            //add to children
            g[*nIt].pred = start;
            //if found in child
            if (limitedDFS(*nIt, end, g, limit-1)) {
                return true;
            }
        }
    }

    //if not found in children, the end is not accecible through this parent
    return false;
}

bool findShortestPathBFS(Graph::vertex_descriptor start, Graph::vertex_descriptor end, Graph& g){
    graphFunctions::clearMarked(g);
    graphFunctions::clearVisited(g);

    //initialize
    std::queue<Graph::vertex_descriptor> frontier;
    frontier.push(start);

    while (!frontier.empty()) {
        //get node
        Graph::vertex_descriptor currentNode = frontier.front();
        frontier.pop();

        //visit node if not visited yet
        if (!g[currentNode].visited) {
            g[currentNode].visited = true;

            //stop if this is the end
            if (currentNode == end) { return true; }

            //add neighbors to queue
            Graph::adjacency_iterator nIt, nEnd;
            boost::tie(nIt, nEnd) = adjacent_vertices(currentNode, g);

            for (; nIt != nEnd; nIt++) {
                if (!g[*nIt].visited && !g[*nIt].marked) {
                    //add to queue
                    g[*nIt].pred = currentNode;
                    g[*nIt].marked = true;
                    frontier.push(*nIt);
                }
            }
        }
    }
    //end not found
    return false;
}

void runBasic(){
    ifstream fin;

    // Read the maze from the file.
    //ask for keyboard input here
    std::cout << "Enter the file name for the maze:\n";
    string fileName;// = "maze_test.txt";
    std::getline(std::cin, fileName);

    //test file validity
    fin.open(fileName.c_str());
    if (!fin){
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

    std::cout << "Recursive DFS with backtracking:\n";
    if (findPathDFSRecursive(*vIt, *(vEnd - 1), m, g)) {
    }
    else {
        std::cout << "No path exists\n";
    }

    std::cout << "DFS using a stack:\n";
    if (findPathDFSStack(*vIt, *(vEnd - 1), g)) {
        std::stack<Graph::vertex_descriptor> s;
        graphToStack(*vIt, *(vEnd - 1), s, g);
        m.printPath(*(vEnd - 1), s, g);
    }
    else {
        std::cout << "No path exists\n";
    }

    std::cout << "Iterative DFS to find shortest path:\n";
    if (findShortestPathDFS(*vIt, *(vEnd - 1), g)) {
        std::stack<Graph::vertex_descriptor> s;
        graphToStack(*vIt, *(vEnd - 1), s, g);
        m.printPath(*(vEnd - 1), s, g);
    }
    else {
        std::cout << "No path exists\n";
    }

    std::cout << "BFS to find shortest path:\n";
    if (findShortestPathBFS(*vIt, *(vEnd - 1), g)) {
        std::stack<Graph::vertex_descriptor> s;
        graphToStack(*vIt, *(vEnd - 1), s, g);
        m.printPath(*(vEnd - 1), s, g);
    }
    else {
        std::cout << "No path exists\n";
    }
}


