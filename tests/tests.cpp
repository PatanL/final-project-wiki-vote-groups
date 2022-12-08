#include "catch.hpp"

#include "../includes/graph.h"

#include <string>
#include <vector>
#include <map>
#include <queue>
 

// TEST_CASE("Graph Built Correctly Small", "[build-graph]") {
//     Graph g("data/test_small.txt");
//     REQUIRE(g.GetNumEdges() == 6);
//     REQUIRE(g.GetNumVertices() == 4);
// }


// TEST_CASE("Graph Built Correctly Large", "[build-graph]") {
//     Graph g("data/test_large.txt");
//     REQUIRE(g.GetNumEdges() == 25);
//     REQUIRE(g.GetNumVertices() == 19);
// }

// TEST_CASE("Graph Built Correctly Main", "[build-graph]") {
//     Graph g("data/wiki-Vote.txt");
//     REQUIRE(g.GetNumEdges() == 103689);
//     REQUIRE(g.GetNumVertices() == 7115);
// }


TEST_CASE("DFS Small", "[build-graph]") {
    Graph g("data/kosa.txt");
    // while (!s.empty()) {
    //     std::cout << s.top() << std::endl;
    //     s.pop();
    // }
    vector<vector<int>> v = g.Kosaraju();
}
TEST_CASE("DFS Small 2", "[build-graph]") {
    Graph g("data/kosa1.txt" );
    // while (!s.empty()) {
    //     std::cout << s.top() << std::endl;
    //     s.pop();
    // }
    vector<vector<int>> v = g.Kosaraju();

}
// TEST_CASE("DFS Small 3", "[build-graph]") {
//     Graph g("data/wiki-Vote.txt" );
//     // while (!s.empty()) {
//     //     std::cout << s.top() << std::endl;
//     //     s.pop();
//     // }
//     vector<vector<int>> v = g.Kosaraju();

// }
// TEST_CASE("Graph::VotesDepthAwayFromMostPopular Small", "[weight=5]") {
//     Graph g("data/test_small.txt");
//     std::vector<int> nodes_depth = g.VotesDepthAwayFromMostPopular();
//     std::vector<int> ans = {1, 1, 2};
//     REQUIRE(nodes_depth == ans);
// }

// TEST_CASE("Graph::ShortestPathFromMostPopular small", "[weight=5]") {
//     Graph g("data/test_small.txt");
//     unordered_map<int, double> nodes_depth = g.ShortestPathFromMostPopular();
//     unordered_map<int, double> ans = {{3, 0}, {1, 1}, {2, 4.0/3}, {4, 4.0/3}};
//     REQUIRE(nodes_depth == ans);
// }
