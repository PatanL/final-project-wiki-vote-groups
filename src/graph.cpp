#include "../includes/graph.h"

#include <cassert>
#include <iostream>
#include <algorithm>

using std::list;
using std::unordered_map;
using std::vector;

Graph::Graph(const std::string& filename): num_edge_(0) {
  ReadGraphData(filename);
  std::cout << num_edge_ << std::endl;
  AddEdgeWeights();
  num_vertex_ = adj_list_.size();
}

Graph::Graph(int vertices) {
  num_vertex_ = vertices;
}

void Graph::addEdge(int source, int destination) {
  adj_list_[source].push_back(Edge(destination, 1));
  adj_list_[destination].push_back(Edge(source, 1));
}

Graph::~Graph() {
  // nothing to deallocate... do nothing
}

int Graph::GetNumEdges() {
  return num_edge_;
}
int Graph::GetNumVertices() {
  return num_vertex_;
}

vector<int> Graph::VotesDepthAwayFromMostPopular() {
  int start = FindMostVotedNode();
  vector<int> node_at_depths;
  // we run bfs on the graph starting from the most popular node
  unordered_map<int, bool> visited;
  assert(visited[0] == false);
  std::queue<std::pair<int, int>> q; // stores node and depth
  visited[start] = true;
  q.push({start, 0});
  while (!q.empty()) {
    int curr_node;
    size_t depth;
    std::tie(curr_node, depth) = q.front();
    q.pop();

    if (depth == node_at_depths.size()) {
      node_at_depths.push_back(0);
    }
    assert(depth < node_at_depths.size());
    node_at_depths.at(depth)++;

    if (NoDirectedAdjacentNodes(curr_node)) {
      continue;
    }

    for (const Edge& e : adj_list_.at(curr_node)) {
      if (!visited[e.dest]) {
        assert(visited.count(e.dest) > 0);
        visited.at(e.dest) = true;
        q.push({e.dest, depth+1});
      }
    }
  }
  return node_at_depths;
}

int Graph::NumberofConnectedComponents() {
  int count = 0;
  unordered_map<int, bool> visited;
  assert(visited[0] == false);
  for(std::pair<int, list<Edge>> v : adj_list_) {
    if(visited[v.first] == false) {
      DFS(v.first, visited);
      count += 1;
      std::cout << v.first << std::endl;
    }
  }
  return count;

}

void Graph::DFS(int v, unordered_map<int, bool>& visited) {
  //mark currennt node as visited
  visited[v] = true;

  list<Edge>::iterator i;

  for(i = adj_list_[v].begin(); i != adj_list_[v].end(); ++i) {
    if(!visited[i->dest]) {
      DFS(i->dest, visited);
    }
  }

}

vector<std::pair<int,int>> Graph::ShortesPathFromMostPopular() {
  int start = FindMostVotedNode();
  // run DFS on the start node in order to get all node in connected component
  unordered_map<int,bool> connected_comp;
  DFS(start, connected_comp);
  vector<int> connected_vertex;
  for (std::pair<int,bool> vertex_pair : connected_comp ){
    connected_vertex.push_back(vertex_pair.first);
  }
  assert(connected_comp.begin()->first == start);
  int numVertex = connected_comp.size();
  // build distance matrix between any two 
  int disMat[numVertex][numVertex];
  for (int row = 0; row < numVertex; row++) {
    for (int col = 0; col < numVertex; col++) {
      // the maximum number of distance between the 2 nodes is the number of vertex + 1
      disMat[row][col] = numVertex+1; 
    }
  }
  disMat[0][0] = 0;
  for (std::pair<int,bool> vertex_pair: connected_comp) {
    int vertex1 = vertex_pair.first;
    // Grab the adjacency list
    list<Edge> v1_adj_list = adj_list_[vertex1];
    for (Edge adj_edge : v1_adj_list) {
      int vertex2 = adj_edge.dest;
      if (std::find(connected_vertex.begin(),connected_vertex.end(), vertex2) != connected_vertex.end()) {
        disMat[vertex1][vertex2] = adj_edge.weight;
      }
    }
  }
  for (int source : connected_vertex) {
    for (int dest: connected_vertex) {
      for (int mid: connected_vertex) {
        if (disMat[source][dest] > disMat[source][mid] + disMat[mid][dest] ) {
          disMat[source][dest] = disMat[source][mid] + disMat[mid][dest] ;
        }
      }
    }
  }
  vector<std::pair<int,int>> output;
  for (int dest: connected_vertex) {
    if (disMat[start][dest] >= numVertex+1) {
      output.push_back({dest, std::numeric_limits<int>::max()});
    } else {
      output.push_back({dest,disMat[start][dest]});
    }
  }
  return output;
}

////////////////////////////////////////
/////   Private Member Functions    ////
////////////////////////////////////////

void Graph::ReadGraphData(const std::string& filename) {
  std::ifstream ifs{filename};
  if (!ifs.is_open()) {
    throw std::runtime_error("Cannot open input file");
  }
  constexpr unsigned weight = 1;
  int src, dest;
  while (ifs >> src >> dest) {
    num_edge_++;

    adj_list_[src].push_back(Edge(dest, weight));
  }
  ifs.close();
}

void Graph::AddEdgeWeights() {
  for (std::pair<const int, list<Edge>>& node : adj_list_) {
    size_t N = node.second.size();
    // update weights for every outgoing edge
    for (Edge& e : node.second) {
      e.weight = 1/static_cast<double>(N);
    }
  }
}

int Graph::FindMostVotedNode() const {
  unordered_map<int, size_t> incoming_edge_cnt;
  for (auto node_it = adj_list_.begin(); node_it != adj_list_.end(); ++node_it) {
    for (const Edge& e : node_it->second) {
      incoming_edge_cnt[e.dest]++;
    }
  }
  auto most_voted_node_it = std::max_element(incoming_edge_cnt.begin(), incoming_edge_cnt.end(), [](const auto& x, const auto& y) {
                          return x.second < y.second;
                        });
  assert(most_voted_node_it->second <= num_edge_);
  return most_voted_node_it->first;
}

bool Graph::NoDirectedAdjacentNodes(int node) const {
  return adj_list_.count(node) == 0;
}