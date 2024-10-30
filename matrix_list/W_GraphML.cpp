#include <iostream>
#include <limits>
#include <list>
using namespace std;

typedef unsigned int Vertex;
typedef unsigned int uint;
typedef float Weight;

class Node {
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

template <typename T> class WeightedGraphML {
private:
  const uint num_vertices;
  uint num_edges;
  double inf = std::numeric_limits<double>::infinity();
  T **adj;

public:
  WeightedGraphML(uint num_vertices) : num_vertices(num_vertices), num_edges(0) {
    const uint ROWS = num_vertices;
    const uint COLS = num_vertices;
    adj = new T *[ROWS + 1];
    for (int i = 0; i < ROWS; i++)
      adj[i] = new T[COLS + 1];
    for (int u = 0; u < ROWS; u++)
      for (int v = 0; v < COLS; v++)
        adj[u][v] = inf;
  }
  ~WeightedGraphML() {
    for (int i = 0; i < num_vertices; i++)
      delete[] adj[i];
    delete[] adj;
  }
  uint get_num_vertices() const { return num_vertices; }
  uint get_num_edges() const { return num_edges; }
  void add_edge(Vertex u, Vertex v, T w) {
    if (adj[u][v] == inf) {
      adj[u][v] = w;
      adj[v][u] = w;
      num_edges++;
    }
  }
  void remove_edge(Vertex u, Vertex v) {
    if (adj[u][v] != inf) {
      adj[u][v] = inf;
      adj[v][u] = inf;
      num_edges--;
    } else
      throw("Edge does not exists");
  }
  void show_graph() const {
    cout << "num_vertices: " << num_vertices << endl;
    cout << "num_edges: " << num_edges << endl;
    for (int u = 0; u < num_vertices; u++) {
      for (int v = 0; v < num_vertices; v++)
        cout << adj[u][v] << " ";
      cout << "\n";
    }
  }
};

int main() {
  uint n_edges, n_vertices;
  cin >> n_vertices >> n_edges;
  WeightedGraphML<Weight> g(n_vertices);
  Vertex u, v;
  Weight w;
  for (uint i = 0; i < n_edges; ++i) {
    cin >> u >> v >> w;
    g.add_edge(u, v, w);
  }
  g.show_graph();
  return 0;
}