#include "../includes/graph.h"

int main() {
    Graph g("data/wiki-Vote.txt");
    std::vector<int> nodes_depths = g.VotesDepthAwayFromMostPopular();
    for (size_t i = 0; i < nodes_depths.size(); ++i) {
        std::cout << "Depth " << i << ": " << nodes_depths.at(i) << " nodes" << std::endl;
    }
    return 0;
}