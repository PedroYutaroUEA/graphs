#include <iostream>
#include <list>
#include <limits>
#include <vector>
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
  Weight weight;

public:
  Node() : value(-1), previous(nullptr), dist(INF), weight(0) {}
  Node(Vertex v) : value(v), previous(nullptr), dist(INF), weight(0) {}
  Node(Vertex v, Weight w) : value(v), previous(nullptr), dist(INF), weight(w) {}

  void setValue(Vertex v) { value = v; }
  Vertex getValue() const { return value; }
  void setPrevious(Node *prev) { previous = prev; }
  Node *getPrevious() const { return previous; }
  void setDist(Dist d) { dist = d; }
  Dist getDist() const { return dist; }
  void setWeight(Weight w) { weight = w; }
  Weight getWeight() const { return weight; }
  bool operator==(const Node &other) const { return value == other.value; }
};

// Classe Graph
class Graph
{
private:
  uint num_vertices;
  list<Node> *adj;
  vector<Node> nodes;

public:
  Graph(uint num_vertices) : num_vertices(num_vertices)
  {
    nodes.resize(num_vertices);
    for (uint i = 0; i < num_vertices; i++)
      nodes[i] = Node(i);
    adj = new list<Node>[num_vertices];
  }

  ~Graph() { delete[] adj; }

  void addEdge(Vertex u, Vertex v, Weight w)
  {
    adj[u].push_back(Node(v, w));
  }

  list<Node> &getAdj(Vertex vertex)
  {
    return adj[vertex];
  }

  Node &getNode(Vertex v)
  {
    return nodes[v];
  }

  vector<Node> &getNodes()
  {
    return nodes;
  }

  void showGraph() const
  {
    for (Vertex v = 0; v < num_vertices; v++)
    {
      cout << v << ": ";
      for (const auto &node : adj[v])
        cout << "(" << node.getValue() << ", " << node.getWeight() << ") ";
      cout << endl;
    }
  }
};

void initialize(Graph &g, Vertex root)
{
  for (Node &v : g.getNodes())
  {
    v.setDist(INF);
    v.setPrevious(nullptr);
  }
  g.getNode(root).setDist(0);
}

void relax(Node &u, Node &v, Weight weight)
{
  if (v.getDist() > u.getDist() + weight)
  {
    v.setDist(u.getDist() + weight);
    v.setPrevious(&u);
  }
}

bool BellmanFord(Graph &g, Vertex root)
{
  initialize(g, root);
  uint num_vertices = g.getNodes().size();
  for (uint i = 0; i < num_vertices - 1; i++)
  {
    for (Vertex u = 0; u < num_vertices; u++)
    {
      Node &uNode = g.getNode(u);
      for (Node &v : g.getAdj(u))
      {
        Node &vNode = g.getNode(v.getValue());
        relax(uNode, vNode, v.getWeight());
      }
    }
  }
  for (Vertex u = 0; u < num_vertices; u++)
  {
    Node &uNode = g.getNode(u);
    for (Node &v : g.getAdj(u))
      if (g.getNode(v.getValue()).getDist() > uNode.getDist() + v.getWeight())
        return false;
  }

  return true;
}

int main()
{
  Graph g1(6);
  g1.addEdge(0, 1, 1);
  g1.addEdge(1, 2, -2);
  g1.addEdge(2, 3, -1);
  g1.addEdge(3, 4, 2);
  g1.addEdge(4, 5, 3);
  g1.addEdge(5, 0, -1);
  g1.showGraph();
  if (BellmanFord(g1, 0))
    cout << "Grafo 1: Nenhum ciclo de peso negativo detectado." << endl;
  else
    cout << "Grafo 1: Ciclo de peso negativo detectado!" << endl;

  Graph g2(6);
  g2.addEdge(0, 1, 1);
  g2.addEdge(1, 2, 2);
  g2.addEdge(2, 3, 3);
  g2.addEdge(3, 4, 4);
  g2.addEdge(4, 5, 5);
  g2.addEdge(0, 5, 6);
  g2.showGraph();

  if (BellmanFord(g2, 0))
    cout << "Grafo 2: Nenhum ciclo de peso negativo detectado." << endl;
  else
    cout << "Grafo 2: Ciclo de peso negativo detectado!" << endl;

  g2.showGraph();
  return 0;
}
