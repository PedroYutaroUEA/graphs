#include <iostream>
#include <list>
using namespace std;

typedef unsigned int Vertex;
typedef unsigned int uint;
typedef float Weight;

class Node
{
private:
  Vertex value;
  Weight weight;

public:
  Node() { value = -1; }
  Node(Vertex v, Weight w) : value(v), weight(w) {}
  void setValue(Vertex v) { value = v; }
  Vertex getValue() const { return value; }
  void setWeight(Weight w) { weight = w; }
  Weight getWeight() const { return weight; }
};

template <typename T>
class WeightedGraphAL
{
private:
  uint num_vertices, num_edges;
  list<T> *adj;

public:
  WeightedGraphAL(uint num_vertices) : num_vertices(num_vertices), num_edges(0)
  {
    adj = new list<T>[num_vertices + 1];
  }
  ~WeightedGraphAL() { delete[] adj; }
  uint get_num_vertices() const { return num_vertices; }
  uint get_num_edges() const { return num_edges; }
  void add_edge(Vertex u, Vertex v, Weight w)
  {
    for (auto vertex : get_adj(u))
      if (vertex.getValue() == v)
        return;
    if (u != v)
    {
      T Node_v(v, w);
      adj[u].push_back(Node_v);
      num_edges++;
    }
  }
  list<T> get_adj(Vertex vertex) const
  {
    list<T> v_list;
    for (const auto &node : adj[vertex])
    {
      Node u = node;
      v_list.push_back(u);
    }
    return v_list;
  }
  void remove_edge(Vertex u, Vertex v)
  {
    for (auto vertex : get_adj(u))
      if (vertex.getValue() == v)
        return;
    if (u != v)
    {
      T Node_v(v);
      adj[u].remove(Node_v);
      num_edges--;
    }
  }

  void show_graph() const
  {
    cout << "num_vertices: " << num_vertices << endl;
    cout << "num_edges: " << num_edges << endl;
    for (Vertex v = 0; v < num_vertices; v++)
    {
      cout << v << ": ";
      list<T> adj_list = get_adj(v);
      for (const auto &node : adj_list)
        cout << "(" << node.getValue() << ", " << node.getWeight() << ")" << ", ";
      cout << endl;
    }
  }

  void printVertexDegreeSum()
  {
    int sum = 0;
    for (Vertex v = 1; v <= num_vertices; v++)
    {
      int degree = get_adj(v).size();
      sum += degree;
    }
    cout << "Sum of degrees: " << sum << endl;
  }

  bool isComplete() const
  {
    for (Vertex v = 1; v <= num_vertices; v++)
    {
      int degree = get_adj(v).size();
      if (degree + 1 != num_vertices)
        return false;
    }
    return true;
  }
};

int main()
{
  uint n_edges, n_vertices;
  cin >> n_vertices >> n_edges;
  WeightedGraphAL<Node> g(n_vertices);
  Vertex u, v;
  Weight w;
  for (uint i = 0; i < n_edges; i++)
  {
    cin >> u >> v >> w;
    g.add_edge(u, v, w);
  }
  g.show_graph();
  return 0;
}