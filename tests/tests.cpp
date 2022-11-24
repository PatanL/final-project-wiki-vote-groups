#include <catch2/catch_test_macros.hpp>
#include <graph.h>
#include <string>
#include <vector>
#include <map>
#include <queue>

// TEST_CASE("VotesDepthAwayFromMostPopular Test 1", "[weight=5]") {
//     Graph g("data/wiki-Vote.txt");
//     std::vector<int> nodes_depths = g.VotesDepthAwayFromMostPopular();
//     std::vector<int> ans = {1, 15, 389, 1713, 198};
//     REQUIRE( nodes_depths == ans );
// }