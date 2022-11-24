#include "../includes/graph.h"

int main() {
    Graph g("data/wiki-Vote.txt");
    std::vector<int> nodes_depths = g.VotesDepthAwayFromMostPopular();
    for (size_t i = 0; i < nodes_depths.size(); ++i) {
        std::cout << "Depth " << i << ": " << nodes_depths.at(i) << " nodes" << std::endl;
    }

    Graph g1(5);
    g1.addEdge(1, 0);
    g1.addEdge(2, 3);
    g1.addEdge(3, 4);
    int num_connected_components = g1.NumberofConnectedComponents();
    std::cout << "Number of Connected Componenets: " << num_connected_components << std::endl;
    return 0;
}