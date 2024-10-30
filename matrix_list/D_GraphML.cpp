#include <iostream>
#include <limits>
#include <list>
using namespace std;

typedef unsigned int Vertex;
typedef unsigned int uint;
typedef unsigned int Weight;

class Node {
private:
  Vertex value;

public:
  Node() { value = -1; }
  Node(Vertex v) { value = v; }
  void setValue(Vertex v) { value = v; }
  Vertex getValue() const { return value; }
};

template <typename T> class DirectedGraphML {
private:
  const uint num_vertices;
  uint num_edges;
  T **adj;

public:
  DirectedGraphML(uint num_vertices) : num_vertices(num_vertices), num_edges(0) {
    const uint ROWS = num_vertices;
    const uint COLS = num_vertices;
    adj = new T *[ROWS + 1];
    for (int i = 0; i < ROWS; i++)
      adj[i] = new T[COLS + 1];
    for (int u = 0; u < ROWS; u++)
      for (int v = 0; v < COLS; v++)
        adj[u][v] = 0;
  }
  ~DirectedGraphML() {
    for (int i = 0; i < num_vertices; i++)
      delete[] adj[i];
    delete[] adj;
  }
  uint get_num_vertices() const { return num_vertices; }
  uint get_num_edges() const { return num_edges; }
  void add_edge(Vertex u, Vertex v, Weight w) {
    if (u != v && adj[u][v] == 0) {
      adj[u][v] = w;
      num_edges++;
    }
  }
  void remove_edge(Vertex u, Vertex v) {
    if (u != v && adj[u][v] == 0) {
      adj[u][v] = 0;
      num_edges--;
    }
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
  DirectedGraphML<Weight> g(n_vertices);
  for (uint i = 0; i < n_edges; ++i) {
    Vertex u, v;
    cin >> u >> v;
    g.add_edge(u, v, 1);
  }
  g.show_graph();
  return 0;
}