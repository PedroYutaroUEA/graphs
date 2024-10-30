#include <iostream>
#include <list>
#include <limits>
#include <vector>
#define INF numeric_limits<Weight>::max()
using namespace std;

typedef unsigned int Vertex, uint;
typedef float Weight;

// dist = soma dos pesos
class Node
{
private:
  Vertex value;
  Node *previous;
  uint dist;
  Weight weight;

public:
  Node() : value(-1), previous(nullptr), dist(INF) {}
  Node(Vertex v) : value(v), dist(INF), weight(INF) {}
  Node(Vertex v, Weight w) : value(v), dist(INF), weight(w) {}

  void setValue(Vertex v) { value = v; }
  Vertex getValue() const { return value; }
  void setPrevious(Node *prev) { previous = prev; }
  Node *getPrevious() const { return previous; }
  void setDist(uint dist) { this->dist = dist; }
  uint getDist() const { return dist; }
  void setWeight(Weight w) { weight = w; }
  Weight getWeight() const { return weight; }
  bool operator==(const Node &other) const { return value == other.value; }
};

class Graph
{
private:
  uint num_vertices, num_edges;
  list<Node> *adj;
  vector<Node> nodes;

public:
  Graph(uint num_vertices) : num_vertices(num_vertices), num_edges(0)
  {
    nodes.resize(num_vertices + 1);
    for (uint i = 0; i < num_vertices + 1; i++)
      nodes[i] = Node(i);
    adj = new list<Node>[num_vertices + 1];
  }

  ~Graph() { delete[] adj; }
  uint getNumVertices() const { return num_vertices; }
  uint getNumEdges() const { return num_edges; }
  void addEdge(Vertex u, Vertex v, Weight w)
  {
    Node Node_v(v, w);
    adj[u].push_back(Node_v);
    num_edges++;
  }

  list<Node> getAdj(Vertex vertex) const
  {
    list<Node> v_list;
    for (const auto &node : adj[vertex])
    {
      Node u = node;
      v_list.push_back(u);
    }
    return v_list;
  }

  void removeEdge(Vertex u, Vertex v)
  {
    Node Node_v(v);
    adj[u].remove(Node_v);
    num_edges--;
  }

  Node &getNode(Vertex v)
  {
    return nodes[v];
  }

  vector<Node> getNodes()
  {
    return nodes;
  }

  void showGraph() const
  {
    cout << "num_vertices: " << num_vertices << endl;
    cout << "num_edges: " << num_edges << endl;
    for (Vertex v = 0; v < num_vertices; v++)
    {
      cout << v << ": ";
      list<Node> adj_list = getAdj(v);
      for (const auto &node : adj_list)
        cout << "(" << node.getValue() << ", " << node.getWeight() << ")" << ", ";
      cout << endl;
    }
  }
};

void initialize(Graph &g, Node &root)
{
  for (Node v : g.getNodes())
  {
    v.setDist(INF);
    v.setPrevious(nullptr);
  }
  root.setDist(0);
}

void relax(Graph &g)
{
  for (uint i = 0; i < g.getNumVertices() - 1; i++)
  {
    for (Node v : g.getNodes())
    {
      for (Node u : g.getAdj(v.getValue()))
      {
        Weight weight = u.getWeight();
        Vertex u_value = u.getValue();
        if (v.getDist() > u.getDist() + weight)
        {
          v.setDist(u.getDist() + weight);
          v.setPrevious(&g.getNode(u_value));
        }
      }
    }
  }
}

int main()
{
}