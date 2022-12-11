## Leading Question 

Are there "political parties" within the wikipedia voting landscape? Wikipedia hosts elections to determine their administrators every couple of months. We will use data about these elections to answer this question.

We will approach this question in two ways.

1. Are there certain groups that are noticabley separate from the rest of the voters in the way they vote. Here we will use the gathered graph data and apply  Kosaraju's algorithm, which finds the strongly connected components of a directed graph, as well as a DFS to determine any separations in the data. The nodes of our graph will be the wikipedia users, the directed edge from node i to node j represents that user i voten on user $j$.

2. Considering the candidate that was most voted for among all elections, on average how many people were voted for each level away from him? Here we will use a BFS and count the number of users at each level away from the most voted for user. This can then be averaged (divide by the highest depth) to get the desired value.

3. We also build on approach (2) to study the geometric structure of the graph by finding the shortest path between every candidate in the same connected component as the most voted for candidate. We will weight edges proportional to the number of votes the source voter cast.

If possible we will try to display these parties if they are detected.

## Dataset Acquisition

We will get the data from the Stanford SNAP dataset (http://snap.stanford.edu/data/wiki-Vote.html)

## Data Format

The input dataset has 103689 edges, hence the dataset in form of edge list has 103689 lines. Each lines contain the id of the one who vote and the id of who received. We will transform this into the adjacency list in order for better graph algorithm runtime.

## Data Correction

We do not believe that there will be much need for data correction beyond converting the given edge list to an adjacency list.

We know there should be 7115 data points in the data. If the number of data points is less than that we will accept the data as correct.

## Data Storage

We will store the text data on our laptop. It will be converted to an adjacency list to store the data as a graph during exection of the program. The adjacency list will be stored as an unordered_map between the src node (int) and the list of outgoing edges in the form of vectors/lists of pairs. Each edge stores the weight (double) and the destination node (int).

We will add weights to the edges based on how many edges go out of the source node. For example, if a node has $N$ outgoing edges, we weight all those edges with $\frac{1}{N}$.

In this form of storage, the expected data storage is $O(n + m)$ where $n$ = # of nodes and $m$ = # of edges.
 
## Algorithm 

We will be using Kosaraju's Algorithm and Depth-first search to find the strongly connected components of the graph data ($O(n + m)$ where $m$ is the number edges). This algorithm will take in the graph as input and output the number of strongly connected components in the graph.

We will also use breadth first search ($O(n + m)$) to compute the average number of people that people that the most popular admin voted for, voted for. We will input the most voted for user and it will output the average value.

We will implement Floyd-Warshall Algorithm to find the shortest path between the most voted for candidate and every other candidate in the same connected component. This will run in $O(n^3)$ where $n$ is the number of nodes.



Th expected space complexity are shown below:

In BFS/DFs, the expected data storage is $O(n)$ ($n$ - number of nodes)

In Kosaraju's SCC, the expected data storage is $O(n)$

In Floyd-Warshall, the expected data storage is $O(n^2)$ as it stores the distance from each node to each other node.

## Timeline

*Week 1*
We will focus on reading in the data and converting it to an adjacency list.

*Week 2*
We will implement the BFS algorithms and begin working with the Floyd-Warshall algorithm.

*Week 3*
Work on strongly-connected component & Begin testing the previously implemented algorithms.

*Week 4*
Complete the algorithms and complete testing.

*Week 5*
Complete any difficult/unfinished parts. Write description of project and create our presentation.