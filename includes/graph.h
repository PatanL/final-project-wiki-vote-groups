#pragma once

#include <algorithm>
#include <unordered_map>
#include <string>
#include <list>
#include <vector>
#include <queue>
#include <fstream>
#include <iostream>

using std::list;
using std::unordered_map;
using std::vector;

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
    ~Graph();

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
     * Gets the number of connected componenets in the graph.
     * @returns The number of connected components.
    */
   int NumberofConnectedComponents();

   /**
    * Runs depth first search on the graph. Marks visited nodes.
    * @param v - the vertex to visit.
   */
  void DFS(int v, unordered_map<int, bool>& visited);
    
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

    /**
     * Find and return the id of the node that has the most incoming edges
     * i.e., the node that was voted for the most times
    */
    int FindMostVotedNode() const;

    bool NoDirectedAdjacentNodes(int node) const;
};