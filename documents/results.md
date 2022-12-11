# Final Report

## Algorithm Overview

### Breadth-First Search

The breadth-first search algorithm is not called explicitly in the main function, however it is necessary to find the number of nodes that are at each depth level away from the most popular node in the graph. Note that the component containing the most popular node is *not* the entire graph. Therefore, the BFS does not end up searching all the nodes in the graph.

The input to the BFS is the graph and the starting node and the output is a vector containing the number of nodes at each depth away from the starting node.

The algorithm runs in $\mathcal{O}(n + m)$ where ( $n$ is the number of edges and $m$ is the number of vertices).

### Floyd-Warshall Shortest Path

Our Floyd-Warshall shortest path algorithm takes the form of the `VotesDepthAwayFromMostPopular()` function. It takes in the input as the graph, and perform the algorithm on the connected component including the most popular node. The output is an unordered map with the node ID as key and the distance away from the most popular node as value. Note that we declare the weight of a vote as 1 / (the number of votes given by that voter).

We verified the result by running on test cases where there are both reachable and unreachable point from the most popular node to ensure only reachable node are added to the map

The algorithm runs in $\mathcal{O}(n^3)$ 

### Kosaraju's Strongly Connected Component

Our Kosaraju's algorithm takes in the graph and perform the algorithm on the whole graph with starting position to be the most popular node. The output is a vector of storngly connected components , which takes form of a vector of integer which is admin ID. We need to implement 2 other specific DFSs as helper function for this algorithm ( we don't specifically write tests for both of the DFSs). In our main file, we'll only print out the number of node inside of the largest strongly connected component, and whether or not the most popular person is inside of it.

We verified the results of this algorithm by writing various smaller test cases for it with our own datasets.

The algorithm runs in $\mathcal{O}(n + m)$ 

## Leading Question
By implementing the aforementioned algorithms, we were able to accomplish our leading goal of “creat[ing] a tool that helps travelers navigate through the dataset.” 

Dijkstra’s, for instance, provides travelers with a GPS that outputs the shortest path from one node (potentially their current location) to another. Travelers seeking a thorough sample of attractions in California without visiting overlapping attractions can use our Welsh-Powell algorithm to retrieve the number of unique samples as well as the attractions corresponding to a particular sample. At the same time, travelers can find the coordinates of the closest attraction to their current location (or any location in California) using our k-nearest neighbors algorithm. Breadth-first search, meanwhile, can be used to obtain a route travelers can use to visit all of the attractions in a particular region of California. The combination of these features creates a robust touring guide to our dataset that could translate to the real world (if it were 2005). 

One of the discoveries we made while implementing the project was that California’s road networks aren’t as densely connected as we believed them to be. Our Welsh-Powell algorithm indicates that three colors is enough to color the entire graph, and our breadth-first search traversal further supports this discovery by only being able to traverse through small connected components We also observed that the attractions in California tend to cluster together in dense groups instead of being evenly dispersed throughout the state.
