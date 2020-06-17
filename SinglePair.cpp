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
    tie(nIt, nEnd) = adjacent_vertices(start, g);

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
            tie(nIt, nEnd) = adjacent_vertices(currentNode, g);

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
    tie(nIt, nEnd) = adjacent_vertices(start, g);

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

bool findShortestPathBFS(Graph::vertex_descriptor start, Graph::vertex_descriptor end, Graph& g)
{
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

            //add neighbors to stack
            Graph::adjacency_iterator nIt, nEnd;
            tie(nIt, nEnd) = adjacent_vertices(currentNode, g);

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

bool graphToStack(Graph::vertex_descriptor start, Graph::vertex_descriptor end, std::stack<Graph::vertex_descriptor>& s, Graph& g){
    Graph::vertex_descriptor currentNode = end;
    while (currentNode != start) {
        s.push(currentNode);
        currentNode = g[currentNode].pred;
    }
    s.push(currentNode);
    return true;
}
