#pragma once

#include <algorithm>
#include <unordered_map>
#include <unordered_set>
#include <string>
#include <list>
#include <vector>
#include <queue>
#include <stack>
#include <fstream>
#include <iostream>
#include <limits>

#define INF std::numeric_limits<double>::max()/2

using std::list;
using std::unordered_map;
using std::unordered_set;
using std::vector;
using std::stack;
using std::queue;

class Graph {
private:
    struct Edge {
        int dest;
        double weight;

        Edge(int d, double w): dest(d), weight{w} {}
    };

public:
    Graph(const std::string &filename);
    Graph(int vertices);

    /**
     * Adds an edge between two vertices
     * @param source - one vertex the edge is connected to
     * param destination - the other vertex the edge is connected to
    */
    void addEdge(int source, int destination);


    /**
     * Return the number of edges / vertices 
     * Mainly used for testing purposes
    */

    int GetNumEdges();

    int GetNumVertices();
    /**
     * @returns vector of integers. The i-th index of the vector is
     * the number of nodes that are separated from the most voted for node
     * by i connections.
    */
    vector<int> VotesDepthAwayFromMostPopular();

    /**
    * Find Shortest Path between most voted candidates vs every
    * other candidates in the same connected component
    * Currently running on an unweigted directed graph, can adjust
    * in order to have weight for each edge
    * @returns the vector of pairs of nodes in connected components
    * and distance from the most popular nodes from it
    * The distance between node to itself is 0
    * The distance between node to an unreachable node is inf
    */ 
    unordered_map<int, double> ShortestPathFromMostPopular();

    /**
     * Run Kosaraju's algorithm for strongly connected component
     * @return A vector of vector of integer, with each vector is 
     * a strongly connected components with int to be the node
    */
    vector<vector<int>> Kosaraju();
    /**
     * Helper function for Kosaraju: run Kosaraju's algorithms on chosen nodes
     * Being put as a public function to help with testing 
     * @return  A vector of vector of integer, with each vector is 
     * a strongly connected components with int to be the node
    */
    vector<vector<int>> Kosaraju(int start);

   /**
     * Find and return the id of the node that has the most incoming edges
     * i.e., the node that was voted for the most times
    */
    int FindMostVotedNode() const;
    
private:
    // we use a map because the indices are not consecutive (i.e., we have nodes labelled as 1, 5, 7, 20,...)
    unordered_map<int, list<Edge>> adj_list_;
    size_t num_edge_;
    int num_vertex_;

    void ReadGraphData(const std::string& filename);

    /**
     * Weights are added to each edge in the graph in the following way:
     * For a given node, the weight of all outgoing edges is set to 1/N,
     * where N is the number of outgoing edges from the node.
    */
    void AddEdgeWeights();

    bool NoDirectedAdjacentNodes(int node) const;

    /**
    * Runs depth first search on the graph. Marks visited nodes.
    * @param v - the vertex to visit.
    * @returns stack containing nodes in the order they are visited
    */
    stack<int> DFS(int start, const unordered_map<int, list<Edge>>& adj_list );

    /**
    * Runs depth first search on the graph , built specific for Kosaraju
    * @param start - The starting vertex
    * @param adj_list - The graph we want to work on
    * @param visited - An empty unordered map, will initialize the map with all nodes visited & value to be true
    * @returns queue containing nodes in the order they are visited
    */
    queue<int> DFS(int start, const unordered_map<int, list<Edge>>& adj_list, unordered_map<int,bool>& visited);

    /**
    * Runs depth first search only on node that have not already been visited , built specific for Kosaraju
    * @param start - The starting vertex
    * @param adj_list - The graph we want to work on
    * @param visited - An unordered map storing whether a node is ever visited in Kosaraju
    * @returns vector containing the all nodes in strongly connected component having starting vertex
    */
    vector<int> KosaDFS(int start,  unordered_map<int, list<Edge>> adj_list, unordered_map<int,bool>& visited );
    /**
    * Initialize the input : an unordered_map with the transpose of the current graph
    * @param trans_adj_list - Empty map we want to initialize
    */
    void Transpose(unordered_map<int,list<Edge>>& trans_adj_list); 
};

/**
* Helper function transforming a stack into a vector
* @param s - the stack that needs to be transformed
* @returns a vector contains all value in stack from the top to the end
*/
template <typename T>
vector<T> StackToVector(stack<T> s) {
    vector<T> output;
    while (!s.empty()) {
        output.push_back(s.top());
        s.pop();
    }
    return output;
}