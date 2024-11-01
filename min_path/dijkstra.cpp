#include <iostream>
#include <list>
#include <limits>
#include <vector>
#include <queue>
#define INF numeric_limits<float>::max()
using namespace std;

typedef unsigned int Vertex, uint;
typedef float Weight, Dist;

// Classe Node
class Node
{
private:
  Vertex value;
  Node *previous;
  Dist dist;

public:
  Node() : value(-1), previous(nullptr), dist(INF) {}
  Node(Vertex v) : value(v), previous(nullptr), dist(INF) {}

  void setValue(Vertex v) { value = v; }
  Vertex getValue() const { return value; }
  void setPrevious(Node *prev) { previous = prev; }
  Node *getPrevious() const { return previous; }
  void setDist(Dist d) { dist = d; }
  Dist getDist() const { return dist; }

  bool operator>(const Node &other) const { return dist > other.dist; }
};

// Classe Graph
class Graph
{
private:
  uint num_vertices;
  list<pair<Vertex, Weight>> *adj;

public:
  Graph(uint num_vertices) : num_vertices(num_vertices)
  {
    adj = new list<pair<Vertex, Weight>>[num_vertices];
  }

  ~Graph() { delete[] adj; }

  void addEdge(Vertex u, Vertex v, Weight w)
  {
    adj[u].push_back(make_pair(v, w));
  }

  const list<pair<Vertex, Weight>> &getAdj(Vertex vertex) const
  {
    return adj[vertex];
  }

  uint getNumVertices() const
  {
    return num_vertices;
  }
};

void dijkstra(const Graph &g, Vertex root, vector<Dist> &distances, vector<Vertex> &previous)
{
  uint num_vertices = g.getNumVertices();
  distances.assign(num_vertices, INF);
  previous.assign(num_vertices, -1);

  // Usar uma fila de prioridade para selecionar o nó com a menor distância
  priority_queue<pair<Dist, Vertex>, vector<pair<Dist, Vertex>>, greater<>> pq;
  distances[root] = 0;
  pq.push(make_pair(0, root));

  while (!pq.empty())
  {
    Vertex u = pq.top().second;
    pq.pop();

    for (const auto &[v, weight] : g.getAdj(u))
    {
      if (distances[v] > distances[u] + weight)
      {
        distances[v] = distances[u] + weight;
        previous[v] = u;
        pq.push(make_pair(distances[v], v));
      }
    }
  }
}

int main()
{
  Graph graph(9);
  graph.addEdge(0, 1, 4.0);
  graph.addEdge(0, 7, 8.0);
  graph.addEdge(1, 2, 8.0);
  graph.addEdge(1, 7, 11.0);
  graph.addEdge(2, 3, 7.0);
  graph.addEdge(2, 8, 2.0);
  graph.addEdge(2, 5, 4.0);
  graph.addEdge(3, 4, 9.0);
  graph.addEdge(3, 5, 14.0);
  graph.addEdge(4, 5, 10.0);
  graph.addEdge(5, 6, 2.0);
  graph.addEdge(6, 7, 1.0);
  graph.addEdge(6, 8, 6.0);
  graph.addEdge(7, 8, 7.0);

  vector<Dist> distances;
  vector<Vertex> previous;
  dijkstra(graph, 0, distances, previous);

  cout << "Minimum Path Tree from Node 0:" << endl;
  for (Vertex v = 0; v < graph.getNumVertices(); ++v)
  {
    cout << "Node " << v << " with distance " << distances[v];
    if (previous[v] != -1)
      cout << " (previous: " << previous[v] << ")";
    cout << endl;
  }

  return 0;
}
