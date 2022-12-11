#include "catch.hpp"

#include "../includes/graph.h"
#include "tests.hpp"

#include <string>
#include <vector>
#include <map>
#include <queue>


////////////////////////////////////////
/////   Testing Helper Functions    ////
////////////////////////////////////////
bool compare_2D_vector(vector<vector<int>> lhs, vector<vector<int>> rhs) {
    if (lhs.size() != rhs.size()) {
        return false;
    }
    for (size_t i = 0; i < lhs.size(); i++) {
        vector<int> l = lhs[i];
        vector<int> r = rhs[i];
        std::sort(l.begin(),l.end());
        std::sort(r.begin(),r.end());
        if (l != r) {
            return false;
        }
    }
    return true;
}
bool compare_map(unordered_map<int,double> lhs, unordered_map<int,double> rhs) {
    if (lhs.size() != rhs.size()) {
        return false;
    }
    for (std::pair<int,double> p: lhs) {
        if (p.second != rhs[p.first]) {
            return false;
        }
    }
    return true;
}

TEST_CASE("Graph Built Correctly Small", "[build-graph]") {
    Graph g("data/test_small.txt");
    REQUIRE(g.GetNumEdges() == 7);
    REQUIRE(g.GetNumVertices() == 6);
}


TEST_CASE("Graph Built Correctly Large", "[build-graph]") {
    Graph g("data/test_large.txt");
    REQUIRE(g.GetNumEdges() == 26);
    REQUIRE(g.GetNumVertices() == 19);
}

TEST_CASE("Graph Built Correctly Main", "[build-graph]") {
    Graph g("data/wiki-Vote.txt");
    // This number was included in the dataset
    REQUIRE(g.GetNumEdges() == 103689);
    REQUIRE(g.GetNumVertices() == 7115);
}

TEST_CASE("Kosaraju Test 1", "[kosaraju]") {
    Graph g("data/kosa1.txt");
    // We will call Kosaraju on node 0
    vector<vector<int>> v = g.Kosaraju(0);
    vector<vector<int>> ans;
    std::vector<int> comp1{0,1,2,3};
    std::vector<int> comp2{4,5,6};
    std::vector<int> comp3{7};
    ans.push_back(comp1);
    ans.push_back(comp2);
    ans.push_back(comp3);
    REQUIRE(compare_2D_vector(v,ans));
}

TEST_CASE("Kosaraju Test 2", "[kosaraju]") {
    Graph g("data/kosa2.txt" );
    vector<vector<int>> v = g.Kosaraju();
    vector<vector<int>> ans;
    std::vector<int> comp1{0,2,3,4,5};
    std::vector<int> comp2{6,7,8};
    ans.push_back(comp1);
    ans.push_back(comp2);
    REQUIRE(compare_2D_vector(v,ans));
}

TEST_CASE("Kosaraju Test 3", "[kosaraju]") {
    Graph g("data/kosa3.txt" );
    vector<vector<int>> result = g.Kosaraju();
    // Expected output: 3 strongly connected components [[0, 1, 2], [3], [4]]
    vector<vector<int>> expected = {{0, 1, 2},
                                    {3},
                                    {4}};
    REQUIRE(compare_2D_vector(result,expected));
}

TEST_CASE("ShortestPathFromMostPopular Small", "[SSSP]") {
    Graph g("data/test_small.txt");
    // The most popular node is node 3
    std::unordered_map<int,double> distance_map = g.ShortestPathFromMostPopular();
    std::unordered_map<int,double> ans;
    ans.insert({3,0});
    ans.insert({1,1});
    ans.insert({4, 4.0 / 3});
    ans.insert({2,4.0 / 3});
    REQUIRE(compare_map(ans,distance_map));
}

TEST_CASE("ShortestPathFromMostPopular Large", "[SSSP]") {
    Graph g("data/test_large.txt");
    // Most popular node is node 5
    std::unordered_map<int,double> distance_map = g.ShortestPathFromMostPopular();
    std::unordered_map<int,double> ans;
    ans.insert({5,0});
    ans.insert({2,0.5});
    ans.insert({19,0.5});
    ans.insert({8,1});
    ans.insert({9,1});
    ans.insert({10,1.25});
    ans.insert({14,1.25});
    ans.insert({18,1.25});
    ans.insert({20,1.25});
    REQUIRE(compare_map(ans,distance_map));
}
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
