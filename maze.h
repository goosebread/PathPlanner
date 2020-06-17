// This file contains the classes originally provided in the maze.h file
#pragma once

#include <iostream>
#include <limits.h>
#include <list>
#include <fstream>
#include <queue>
#include <vector>
#include <stack>

#include "d_except.h"
#include "d_matrix.h"
#include "graph.h"

#define LargeValue 99999999

class maze
{
public:
   // Initializes a maze by reading values from fin.  Assumes that the
   // number of rows and columns indicated in the file are correct.
   maze(ifstream &fin);

   // Print out a maze, with the goal and current cells marked on the board.
   void print(int,int,int,int);

   // Return the value stored at the (i,j) entry in the maze, indicating
   // whether it is legal to go to cell (i,j).
   bool isLegal(int i, int j);

   // Create a graph g that represents the legal moves in the maze m.
   void mapMazeToGraph(Graph &g);
   
   //prints the nodes in the stack starting from the top and ending with end
   void printPath(Graph::vertex_descriptor end,
       std::stack<Graph::vertex_descriptor> &s, Graph &g);

   //Accessor functions
   int numRows(){return rows;};
   int numCols(){return cols;};

private:
   int rows; // number of rows in the maze
   int cols; // number of columns in the maze12 a
   
   //matrix holding the maze 
   matrix<bool> value;
};


