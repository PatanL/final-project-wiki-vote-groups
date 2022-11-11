#pragma once

#include <unordered_map>
#include <string>
#include <algorithm>
#include <vector>
#include <list>
#include <fstream>
#include <iostream>

using namespace std;
class Graph {
private:
    struct Edge {
        int dest;
        double weight;

        Edge(int d, double w): dest(d), weight{w} {}
    };

public:
    Graph(const std::string &filename);
    
private:
    unordered_map<int , list<Edge>> adj_list;
    int num_edge;
    // int num_vertex;
};