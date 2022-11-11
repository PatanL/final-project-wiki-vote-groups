#include "../includes/graph.h"

using namespace std;

Graph::Graph(const std::string& filename): num_edge(0) {
    ifstream ifs{filename};
    if (!ifs.is_open()) {
      cout << "Cannot open input file" << endl;
  }
  constexpr unsigned weight = 1;
  int src, dest;
  // unsigned line_num = 0;
  while (ifs >> src >> dest) {
    num_edge++;

    adj_list[src].push_back(Edge(dest, weight));

    // if (adj_list.find(src) == adj_list.end()) { // if src not found
    //   list<Edge> adjacent = {Edge(dest, 1)};
    //   adj_list.insert({src, adjacent});
    // } else {
    //   unordered_map<int,double> map = adj_list[src];
    //   if (map.find(dest) != map.end()) {
    //       std::cout << "Line " << line_num << " is duplicated" << endl;
    //       continue;
    //   } else {
    //       map.insert({dest,1});
    //   }
    // }
    // line_num++;
  }
  std::cout << num_edge << endl;
  // std::cout << num_vertex << endl;

  ifs.close();
    
}