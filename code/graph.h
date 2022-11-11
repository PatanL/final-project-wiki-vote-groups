#pragma once


#include <unordered_map>
#include <vector>
#include <fstream>


using namespace std;
class Graph {
    public:
        Graph(const std::string &filename);
    private:
        unordered_map<int , unordered_map<int, double> > adj_list;
        int num_edge;
        int num_vertex;
};