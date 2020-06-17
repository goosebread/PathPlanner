//Team Sombrero


#include "maze.h"
#include "SinglePair.h"

int main()
{
    try
    {
        ifstream fin;

        // Read the maze from the file.
        string fileName = "maze_test.txt";

        fin.open(fileName.c_str());
        if (!fin)
        {
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

        tie(vIt, vEnd) = vertices(g);
        //vEnd is a sentinel
        cout << *vIt << " " << *(vEnd-1) << std::endl;
        if (findShortestPathDFS(*vIt, *(vEnd - 1), g)) {
            std::stack<Graph::vertex_descriptor> s;
            graphToStack(*vIt, *(vEnd - 1), s, g);
            m.printPath(*(vEnd - 1), s, g);
        }
        else { std::cout << "no path"; }
        

        //std::cout << g;

    }
    catch (const char* msg) {
        std::cerr << msg << "\n";
    }
    return 0;
}
