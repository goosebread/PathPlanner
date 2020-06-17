#include "maze.h"

//This file contains function definitions for the maze class
using namespace std;

maze::maze(ifstream& fin)
// Initializes a maze by reading values from fin.  Assumes that the
// number of rows and columns indicated in the file are correct.
{
    fin >> rows;
    fin >> cols;

    char x;

    value.resize(rows, cols);
    for (int i = 0; i <= rows - 1; i++)
        for (int j = 0; j <= cols - 1; j++)
        {
            fin >> x;
            if (x == 'O')
                value[i][j] = true;
            else
                value[i][j] = false;
        }

}

void maze::print(int goalI, int goalJ, int currI, int currJ)
// Print out a maze, with the goal and current cells marked on the board.
{
    cout << endl;

    if (goalI < 0 || goalI > rows || goalJ < 0 || goalJ > cols)
        throw rangeError("Bad value in maze::print");

    if (currI < 0 || currI > rows || currJ < 0 || currJ > cols)
        throw rangeError("Bad value in maze::print");

    for (int i = 0; i <= rows - 1; i++)
    {
        for (int j = 0; j <= cols - 1; j++)
        {
            if (i == goalI && j == goalJ)
                cout << "*";
            else
                if (i == currI && j == currJ)
                    cout << "+";
                else
                    if (value[i][j])
                        cout << " ";
                    else
                        cout << "X";
        }
        cout << endl;
    }
    cout << endl;
}

bool maze::isLegal(int i, int j)
// Return the value stored at the (i,j) entry in the maze, indicating
// whether it is legal to go to cell (i,j).
{
    if (i < 0 || i > rows || j < 0 || j > cols)
        throw rangeError("Bad value in maze::isLegal");

    return value[i][j];
}

void maze::mapMazeToGraph(Graph& g) {
    // Create a graph g that represents the legal moves in the maze m.

    //assume non-empty square matrix. do checks later

    //array holding upper row values and previous stuff 
    //contains information of the previous row as the matrix is read
    std::vector<bool> previousValid;
    previousValid.resize(cols);
    std::vector<Graph::vertex_descriptor> previousNodes;
    previousNodes.resize(cols);


    //add first row and check for left connections
    //also fills values for the top row vectors
    bool leftCell = false;
    for (int c = 0; c < cols; c++) {
        //if free cell
        if (value[0][c]) {
            Graph::vertex_descriptor newNode = add_vertex(g);
            g[newNode].cell = { 0, c };

            //check for edge on left
            if (leftCell) {
                add_edge(newNode, previousNodes.at(c - 1), g);
            }


            leftCell = true;
            previousValid.at(c) = true;
            previousNodes.at(c) = newNode;
        }
        else {
            leftCell = false;
            previousValid.at(c) = false;
        }
    }

    //add all other rows and check for left and up connections
    for (int r = 1; r < rows; r++) {

        bool leftCell = false;
        for (int c = 0; c < cols; c++) {
            //if free cell
            if (value[r][c]) {
                Graph::vertex_descriptor newNode = add_vertex(g);
                g[newNode].cell = { r, c };

                //check for edge on left
                if (leftCell) {
                    add_edge(newNode, previousNodes.at(c - 1), g);
                }
                //edge above
                if (previousValid.at(c)) {
                    add_edge(newNode, previousNodes.at(c), g);
                }

                //update the rows in memory
                leftCell = true;
                previousValid.at(c) = true;
                previousNodes.at(c) = newNode;
            }
            else {
                leftCell = false;
                previousValid.at(c) = false;
            }
        }
    }
}

void maze::printPath(Graph::vertex_descriptor end,
    std::stack<Graph::vertex_descriptor>& s, Graph& g) {
    
    //throw error for empty stack or if the end is wrong

    while (!s.empty()) {
        //get node
        Graph::vertex_descriptor currentNode = s.top();
        s.pop();
        //use print() to show each step 
        print(g[end].cell.first, g[end].cell.second, g[currentNode].cell.first, g[currentNode].cell.second);
    }
}