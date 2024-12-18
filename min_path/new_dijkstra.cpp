#include <iostream>
#include <list>
#include <limits>
#include <vector>
#define INF numeric_limits<Weight>::max()
using namespace std;

typedef unsigned int Vertex;
typedef float Weight, Dist;

// Classe Node
class Edge
{
  Vertex u, v;
  Weight weight;
};

// Classe Graph
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

// Fila de prioridade implementada manualmente
template <typename T>
class PriorityQueue
{
private:
  vector<T> heap;

  void heapifyUp(int index)
  {
    while (index > 0 && heap[(index - 1) / 2].first > heap[index].first)
    {
      swap(heap[index], heap[(index - 1) / 2]);
      index = (index - 1) / 2;
    }
  }

  void heapifyDown(int index)
  {
    int size = heap.size();
    int smallest = index;
    int left = 2 * index + 1;
    int right = 2 * index + 2;

    if (left < size && heap[left].first < heap[smallest].first)
      smallest = left;
    if (right < size && heap[right].first < heap[smallest].first)
      smallest = right;
    if (smallest != index)
    {
      swap(heap[index], heap[smallest]);
      heapifyDown(smallest);
    }
  }

public:
  bool isEmpty() const
  {
    return heap.empty();
  }

  void insert(T node)
  {
    heap.push_back(node);
    heapifyUp(heap.size() - 1);
  }

  T extractMin()
  {
    if (heap.empty())
      throw runtime_error("Heap is empty");
    T minNode = heap[0];
    heap[0] = heap.back();
    heap.pop_back();
    if (!heap.empty())
      heapifyDown(0);
    return minNode;
  }

  T extractMax()
  {
    if (heap.empty())
      throw runtime_error("Heap is empty");

    // Encontrar o nó com o valor máximo
    int maxIndex = 0;
    for (int i = 1; i < heap.size(); ++i)
    {
      if (heap[i].first > heap[maxIndex].first)
      {
        maxIndex = i;
      }
    }
    T maxNode = heap[maxIndex];
    heap[maxIndex] = heap.back();
    heap.pop_back();
    if (!heap.empty())
      heapifyDown(maxIndex);
    return maxNode;
  }

  T getMin() const
  {
    if (heap.empty())
      throw runtime_error("Heap is empty");
    return heap[0];
  }

  T getMax() const
  {
    if (heap.empty())
      throw runtime_error("Heap is empty");

    // Encontrar o nó com o valor máximo
    int maxIndex = 0;
    for (int i = 1; i < heap.size(); ++i)
    {
      if (heap[i].first > heap[maxIndex].first)
      {
        maxIndex = i;
      }
    }
    return heap[maxIndex];
  }

  void decreaseKey(Vertex v, Dist newDist)
  {
    for (size_t i = 0; i < heap.size(); i++)
    {
      if (heap[i].second == v)
      {
        heap[i].first = newDist;
        heapifyUp(i);
        return;
      }
    }
  }
};
void dijkstra(const Graph &g, Vertex root, vector<Dist> &distances, vector<Vertex> &previous)
{
  int num_vertices = g.getNumVertices();
  distances.assign(num_vertices, INF);
  previous.assign(num_vertices, INF);

  // Usar uma fila de prioridade para selecionar o nó com a menor distância
  PriorityQueue<pair<Dist, Vertex>> pq;
  distances[root] = 0;
  pq.insert(make_pair(0, root));

  while (!pq.isEmpty())
  {
    Vertex u = pq.extractMin().second;

    for (const auto &[v, weight] : g.getAdj(u))
    {
      if (distances[v] > distances[u] + weight)
      {
        distances[v] = distances[u] + weight;
        previous[v] = u;
        pq.insert(make_pair(distances[v], v));
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
    if (previous[v] != INF)
      cout << " (previous: " << previous[v] << ")";
    cout << endl;
  }

  return 0;
}
