#include <iostream>
#include <list>
#include <limits>
#include <vector>
#define INF numeric_limits<Weight>::max()
using namespace std;

typedef unsigned int Vertex;
typedef float Weight, Dist;

struct Edge
{
  Vertex u, v;
  Weight weight;
};

class Graph
{
private:
  int num_vertices;
  list<pair<Vertex, Weight>> *adj;

public:
  Graph(int num_vertices) : num_vertices(num_vertices)
  {
    adj = new list<pair<Vertex, Weight>>[num_vertices];
  }

  ~Graph() { delete[] adj; }

  void addEdge(Vertex u, Vertex v, Weight w)
  {
    adj[u].push_back(make_pair(v, w));
    adj[v].push_back(make_pair(u, w));
  }

  const list<pair<Vertex, Weight>> &getAdj(Vertex vertex) const
  {
    return adj[vertex];
  }

  int getNumVertices() const
  {
    return num_vertices;
  }
};

class UnionFind
{
private:
  vector<Vertex> vertices;
  vector<Vertex> parent;

public:
  UnionFind(int num_vertices) : vertices(num_vertices), parent(num_vertices) {}

  void makeSet(Vertex vertex)
  {
    parent[vertex] = vertex;
  }

  Vertex findSet(Vertex vertex)
  {
    if (parent[vertex] != vertex)
      parent[vertex] = findSet(parent[vertex]);
    return parent[vertex];
  }

  void unionSet(Vertex vertex1, Vertex vertex2)
  {
    Vertex parent1 = findSet(vertex1);
    Vertex parent2 = findSet(vertex2);
    if (parent1 != parent2)
      parent[parent1] = parent2;
  }
};

Weight MST_Kurskal(Graph &g)
{
  list<Edge> T;
  int num_vertices = g.getNumVertices();
  UnionFind uf(num_vertices);
  Weight total_weight = 0.0;
  // make sets for each vertex
  for (Vertex v = 0; v < num_vertices; ++v)
    uf.makeSet(v);
  // order edges
  list<Edge> edges;
  for (Vertex u = 0; u < num_vertices; ++u)
  {
    const list<pair<Vertex, Weight>> &adj_list = g.getAdj(u);
    for (auto &edge : adj_list)
      edges.push_back({u, edge.first, edge.second});
  }
  edges.sort(
      [](const Edge &e1, const Edge &e2)
      { return e1.weight < e2.weight; });
  for (auto &edge : edges)
  {
    Vertex u = edge.u;
    Vertex v = edge.v;
    Weight weight = edge.weight;
    if (uf.findSet(u) != uf.findSet(v))
    {
      uf.unionSet(u, v);
      T.push_back({u, v, weight});
      total_weight += weight;
    }
  }
  return total_weight;
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

  Weight weights = MST_Kurskal(graph);

  cout << "Weight: " << weights << endl;

  return 0;
}
