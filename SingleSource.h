#pragma once



/*

(f) Write a global function relax(Graph &g, vertex descriptor u, vertex descriptor v) that relaxes
the edge between nodes u and v.
(g) Write a global function dijkstra(Graph &g, vertex descriptor) that uses Dijsktra’s algorithm to
search for a shortest path from node s to every node in g, where all node weights must be positive.
Sets each node’s pred field equal to the predecessor node in a shortest path from node s, if such
a path exists. If a path exists to every node, returns true and returns false otherwise. Use a priority
queue based on a min-heap to store the nodes and find the one with the smallest value. Use the weight
property of nodes to store the shortest path estimates. Use heapV::minHeapDecreaseKey(v) to update
the estimates for node v. The function is passed the index i of a node. Use heapV::getIndex(v) to
find this index value.
(h) Write a global function bellmanFord(Graph &g, vertex descriptor s) that uses the Bellman-Ford
algorithm to search for a shortest path from node s to every node in g, where the graph can have
negative edge weights. Sets each node’s pred field equal to the predecessor node in a shortest path
from node s, if such a path exists. If a negative cycle is reachable from s, returns false and returns true
otherwise. Use node weights to store the node values.


For parts (g)-(h), apply your algorithms to the graph files. The files include the number of nodes, the start
node and the end node. The code you submit should read a graph’s file name from the keyboard, apply
both shortest path functions to the graph, and then print the sequence of nodes in a shortest path to the
end node. If a shortest path to the end node does not exist, your code should print “no shortest path
exists”.


*/