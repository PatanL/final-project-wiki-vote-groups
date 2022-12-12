#include "../includes/graph.h"

#include <cassert>
#include <iostream>

Graph::Graph(const std::string& filename): num_edge_(0) {
  ReadGraphData(filename);
  AddEdgeWeights();
}

Graph::Graph(int vertices) {
  num_vertex_ = vertices;
}

void Graph::addEdge(int source, int destination) {
  adj_list_[source].push_back(Edge(destination, 1));
  adj_list_[destination].push_back(Edge(source, 1));
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

vector<vector<int>> Graph::Kosaraju() {
  // We will call the helper function with the starting node to be our most voted node
  int start = FindMostVotedNode();
  return Kosaraju(start);
}

vector<vector<int>> Graph::Kosaraju(int start) {
  vector<vector<int>> output;
  std::unordered_map<int,bool> visited;
  
  //Call our DFS that return a queue, which will initialize visited with all nodes in connected components & true
  queue<int> connected_comp= DFS(start,adj_list_,visited); 

  // After DFS, all value in visited become true, thus we flip it to make more sense later on
  for (std::pair<int,bool> p : visited) {
    visited[p.first] = false;
  } 

  // Obtain the transpose adj_list
  unordered_map<int,list<Edge>> transpose;
  Transpose(transpose);


  // Kosaraju
  while (!connected_comp.empty() ) {
    int cur = connected_comp.front();
    connected_comp.pop();
    if (visited[cur]) {
      continue;
    }
    // Call Kosaraju DFS to get the vector of nodes in the connected components that include the current node
    std::vector<int> s = KosaDFS(cur, transpose,visited);
    output.push_back(s);
  }
  return output;
}


unordered_map<int, double> Graph::ShortestPathFromMostPopular() {
  int start = FindMostVotedNode();

  unordered_map<int, int> indices;

  // run DFS on the start node in order to get all node in connected component
  vector<int> connected_vertex = StackToVector(DFS(start, adj_list_));
  int numVertex = connected_vertex.size();
  for (int i = 0; i < numVertex; ++i) {
    indices.insert({connected_vertex[i], i});
  }
  // build distance matrix between any two 
  vector<vector<double>> disMat(numVertex, vector<double>(numVertex, INF));

  // adding weights to dist matrix
  for (int v1 : connected_vertex) {
    if (NoDirectedAdjacentNodes(v1)) {
      continue;
    }
    int v1_idx = indices.at(v1);
    list<Edge> v1_adj_list = adj_list_.at(v1);
    disMat.at(v1_idx).at(v1_idx) = 0;
    for (const Edge& adj_edge : v1_adj_list) {
      int v2_idx = indices.at(adj_edge.dest);
      disMat.at(v1_idx).at(v2_idx) = adj_edge.weight;
    }
  }
  // compute distances
  for (int source : connected_vertex) {
    int src_idx = indices.at(source);
    if (src_idx % 100 == 0)
      std::cout << src_idx << '\n';
    for (int dest : connected_vertex) {
      int dest_idx = indices.at(dest);
      for (int mid : connected_vertex) {
        int mid_idx = indices.at(mid);
        disMat[src_idx][dest_idx] = std::min(disMat[src_idx][dest_idx], disMat[src_idx][mid_idx] + disMat[mid_idx][dest_idx]);
      }
    }
  }

  unordered_map<int, double> dist_to_start;
  for (int dest : connected_vertex) {
    dist_to_start.insert({dest, disMat[indices.at(start)][indices.at(dest)]});
  }
  return dist_to_start;
}

////////////////////////////////////////
/////   Private Member Functions    ////
////////////////////////////////////////

void Graph::ReadGraphData(const std::string& filename) {
  std::ifstream ifs{filename};
  if (!ifs.is_open()) {
    throw std::runtime_error("Cannot open input file");
  }

  unordered_set<int> vertices;
  constexpr unsigned weight = 1;
  int src, dest;
  while (ifs >> src >> dest) {
    num_edge_++;
    vertices.insert(src);
    vertices.insert(dest);
    adj_list_[src].push_back(Edge(dest, weight));
  }
  num_vertex_ = vertices.size();
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

stack<int> Graph::DFS(int start, const unordered_map<int, list<Edge>>& adj_list) {
  unordered_map<int, bool> visited;
  stack<int> visited_nodes;
  stack<int> s;
  visited[start] = true;
  s.push(start);
  while (!s.empty()) {
    int curr_node = s.top();
    s.pop();
    visited_nodes.push(curr_node);

    if (adj_list.count(curr_node) == 0) {
      continue;
    }

    for (const Edge& e : adj_list.at(curr_node)) {
      if (!visited[e.dest]) {
        visited.at(e.dest) = true;
        s.push(e.dest);
      }
    }
  }
  return visited_nodes;
}
vector<int> Graph::KosaDFS(int start,  unordered_map<int, list<Edge>> adj_list, unordered_map<int,bool>& visited) {
  // Normal Traversal 
  unordered_map<int, bool> v;
  stack<int> visited_nodes;
  vector<int> output;
  visited_nodes.push(start);
  while (!visited_nodes.empty()) {
    int curr_node = visited_nodes.top();
    visited_nodes.pop();
    // Only difference is we always check for already visited node before working on any node
    if (visited[curr_node]) {
      continue;
    }
    output.push_back(curr_node);
    visited[curr_node] = true;
    if (adj_list.count(curr_node) == 0) {
      continue;
    }

    for (const Edge& e : adj_list.at(curr_node)) {
      // Check if the node is ever visited before
      if (!visited[e.dest]) {
        visited_nodes.push(e.dest);
      }
    }
  }
  return output;
}


queue<int> Graph::DFS(int start, const unordered_map<int, list<Edge>>& adj_list, unordered_map<int,bool>& visited) {
  queue<int> visited_nodes;
  stack<int> s;
  visited[start] = true;
  s.push(start);
  while (!s.empty()) {
    int curr_node = s.top();
    s.pop();
    visited_nodes.push(curr_node);

    if (adj_list.count(curr_node) == 0) {
      continue;
    }

    for (const Edge& e : adj_list.at(curr_node)) {
      if (!visited[e.dest]) {
        visited.at(e.dest) = true;
        s.push(e.dest);
      }
    }
  }
  return visited_nodes;
}
  

void Graph::Transpose(unordered_map<int,list<Edge>>& trans_adj_list) {
  for (std::pair<int,list<Edge>> p : adj_list_) {
    int start = p.first;
    for (Edge e : p.second) {
      int dest = e.dest;
      int weight = e.weight;
      trans_adj_list[dest].push_back(Edge(start,weight));
    }
  }
}