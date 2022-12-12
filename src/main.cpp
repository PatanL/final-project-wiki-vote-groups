#include "../includes/graph.h"



int main(int argc, char* argv[]) {
    if (argc == 1) {
        std::cout << "Please input a data file\n";
        return 1;
    }
    if (argc > 2) {
        std::cout << "More than one input given. Only the first one will be used.\n";
    }
    // We first build our graph out of the wiki-Vote dataset
    Graph g(argv[1]);
    // We first find the most popular vertices, or in this particular cases, the most voted admin.
    std::cout << "The most popular admin ID is : " << g.FindMostVotedNode() << std::endl;
    /**
     * We start with our second proposal: On average, how many people were voted for each level away 
     * from most popular admin.
     * This can be rephrased as finding the average depth of all reachable node from most popular.
    */
    std::cout << "Proposal 2" << std::endl;
    std::cout << "The number of nodes at each level away from the most popular node are :" << std::endl;
    std::vector<int> nodes_depths = g.VotesDepthAwayFromMostPopular();
    float average_depth = 0;
    int num_node = 0;
    for (size_t i = 0; i < nodes_depths.size(); ++i) {
        std::cout << "Depth " << i << ": " << nodes_depths.at(i) << " nodes" << std::endl;
        average_depth += nodes_depths.at(i) *i;
        num_node += nodes_depths.at(i);
    }
    std::cout << "On average, the average number of votes away of all reachable admin from most popular person is : " << average_depth/num_node <<std::endl;

    /**
     * We'll discuss the next prompt: finding if there are any noticable "political party" inside of the vote,
     * where people inside of the groups votes and get voted from other person from the party. 
     * We'll use the Kosaraju's strongly connected component algorithm starting from the most popular node 
     * to handle this.
    */
    std::cout << "Proposal 1" << std::endl;
    std::vector<std::vector<int>> strongly_connected_comps = g.Kosaraju();
    size_t max_num_node = 0;
    size_t max_idx = 0;
    for (size_t idx = 0; idx < strongly_connected_comps.size(); idx++) {
        std::vector<int> scc = strongly_connected_comps.at(idx);
        if (scc.size() > max_num_node) {
            max_num_node = scc.size();
            max_idx = idx;
        }
    }
    if (max_idx == 0) {
        std::cout << "The largest 'political party' contains " << max_num_node << " admins. Moreover, the most popular node is also a part of it" <<std::endl;
    } else {
        std::cout << "The largest 'political party' contains " << max_num_node << " admins. However, the most popular node is not a part of it" <<std::endl;
    }
    /**
     * We'll discuss our additional  prompt: finding the furthese reachable person from the most popular, given the weight 
     * of each vote is 1 / (number of votes of the voter)
     * We'll use the Floyd-Warshall's SSSP to handle this
     * Note: This function will take a lot longer to run compared to the rest 
    */
    std::cout << "Proposal 3: " <<std::endl;
    std::unordered_map<int,double> sssp = g.ShortestPathFromMostPopular();
    int furthest_reachable_person = 0;
    float furthest_distance =0;
    for (std::pair<int,double> person: sssp) {
        if (person.first > furthest_distance) {
            furthest_reachable_person = person.first;
            furthest_distance = person.second;
        }
    }
    std::cout << "The furthese reachable person id is " <<furthest_reachable_person << " << std::endl;
    return 0;
}