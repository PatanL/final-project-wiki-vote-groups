#include "catch.hpp"

#include "../includes/graph.h"

#include <string>
#include <vector>
#include <map>
#include <queue>
 

TEST_CASE("GraphBuiltCorrectly::Small", "[build-graph]") {
    Graph g("data/test_small.txt");
    REQUIRE(g.GetNumEdges() == 5);
    REQUIRE(g.GetNumVertices() == 4);
}


TEST_CASE("GraphBuiltCorrectly::Large", "[build-graph]") {
    Graph g("data/test_large.txt");
    REQUIRE(g.GetNumEdges() == 25);
    REQUIRE(g.GetNumVertices() == 19);
}

TEST_CASE("GraphBuiltCorrectly::Main", "[build-graph]") {
    Graph g("data/wiki-Vote.txt");
    REQUIRE(g.GetNumEdges() == 103689);
    REQUIRE(g.GetNumVertices() == 7115);
}

// TEST_CASE("")


TEST_CASE("VotesDepthAwayFromMostPopular::Small", "[weight=5]") {
    Graph g("data/test_small.txt");
    std::vector<int> nodes_depth = g.VotesDepthAwayFromMostPopular();
    std::vector<int> ans = {1,3};
    REQUIRE(nodes_depth == ans);
}