# Final Report

## Algorithm Overview

### Breadth-First Search

The breadth-first search algorithm is not called explicitly in the main function, however it is necessary to find the number of nodes that are at each depth level away from the most popular node in the graph. Note that the component containing the most popular node is *not* the entire graph. Therefore, the BFS does not end up searching all the nodes in the graph.

The input to the BFS is the graph and the starting node and the output is a vector containing the number of nodes at each depth away from the starting node.

The algorithm runs in $\mathcal{O}(n + m)$ where ( $n$ is the number of edges and $m$ is the number of vertices).

We verified that the BFS was correct by running test cases using a smaller dataset and ensuring it worked as intended.

### Floyd-Warshall Shortest Path

Our Floyd-Warshall shortest path algorithm takes the form of the `VotesDepthAwayFromMostPopular()` function. It takes in the input as the graph, and perform the algorithm on the connected component including the most popular node. The output is an unordered map with the node ID as key and the distance away from the most popular node as value. Note that we declare the weight of a vote as 1 / (the number of votes given by that voter).

We verified the result by running on test cases where there are both reachable and unreachable point from the most popular node to ensure only reachable node are added to the map

The algorithm runs in $\mathcal{O}(n^3)$ 

### Kosaraju's Strongly Connected Component

Our Kosaraju's algorithm takes in the graph and perform the algorithm on the whole graph with starting position to be the most popular node. The output is a vector of storngly connected components , which takes form of a vector of integer which is admin ID. We need to implement 2 other specific DFSs as helper function for this algorithm ( we don't specifically write tests for both of the DFSs). In our main file, we'll only print out the number of node inside of the largest strongly connected component, and whether or not the most popular person is inside of it.

We verified the results of this algorithm by writing various smaller test cases for it with our own datasets.

The algorithm runs in $\mathcal{O}(n + m)$ 

## Leading Question
By implementing the aforementioned algorithms, we were able to accomplish our leading goal of “Trying to understand more of the voting scheme inside of Wikipedia, as well as finding whether or not are there a 'political party' inside of it” 

The BFS gives us an understanding of who is the most voted person (person id 4037), which is needed for all other remaining functionas well as how in average ,"far away" in terms of votes are other person from him/her ( 2.90328 votes depth away in average)

Our Floyd-Warshall algorithm has shown what is the distance from that most voted nodes/person to all other reachable person when given weight to each edge, and also finding out who is the furthest from most popular (out of all those are reachable), which is person 5158

Finally, our Kosaraju's Strongly Connected Component has found the largest "political party" inside of the voting landscape, which contains up to 5158 person, where any person can be reached by all other person inside the component. 
