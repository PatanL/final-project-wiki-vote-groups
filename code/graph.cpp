#include "graph.h"
#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

Graph::Graph(const std::string& filename):num_edge(0),num_vertex(0) {
    ifstream file(filename);
    if (!file.is_open()){
      cout << "Cannot open input file" << endl;
  }
  string line;
  int line_num = 0;
  while (getline(file,line)) {
    string s1;
    string s2;
    bool isFirstID = true;
    for (char& c: line) {
      if (!isdigit(c)) {
        isFirstID = false;
      } else {
        if (isFirstID) {
          s1 += c;
        } else {
          s2 +=  c;
        }
      }
    }
    int id1 = std::stoi(s1);
    int id2 = std::stoi(s2);
    if (id1 == 0 || id2 == 0) {
        std::cout << "Line " << line_num << " cannot be read properly" << endl;
        continue;
    }
    num_edge++;
    if (adj_list.find(id1) == adj_list.end()) {
      num_vertex ++;
      unordered_map<int,double> map;
      map.insert({id2,1});
      adj_list.insert({id1,map});
    } else {
      unordered_map<int,double> map = adj_list[id1];
      if (map.find(id2) != map.end()) {
          std::cout << "Line " << line_num << " is duplicated" << endl;
          continue;
      } else {
          map.insert({id2,1});
      }
    }
    line_num ++;
  }
  std::cout << num_edge << endl;
  std::cout << num_vertex << endl;
  std::cout << adj_list.count(30) << std::endl;

  file.close();
    
}