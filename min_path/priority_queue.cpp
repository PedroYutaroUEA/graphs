#include <iostream>
#include <vector>
#include <limits>
#define INF std::numeric_limits<float>::max()
using namespace std;

typedef unsigned int Vertex;
typedef float Weight, Dist;

// Classe Node para representar cada vértice do grafo
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
  Node(Vertex v, Weight w) : value(v), previous(nullptr), dist(w), weight(w) {} // Corrigido

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

// Fila de prioridade implementada manualmente
template <typename T>
class PriorityQueue
{
private:
  vector<T> heap;

  void heapifyUp(int index)
  {
    while (index > 0 && heap[(index - 1) / 2].getDist() > heap[index].getDist())
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

    if (left < size && heap[left].getDist() < heap[smallest].getDist())
      smallest = left;
    if (right < size && heap[right].getDist() < heap[smallest].getDist())
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
      if (heap[i].getDist() > heap[maxIndex].getDist())
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
      if (heap[i].getDist() > heap[maxIndex].getDist())
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
      if (heap[i].getValue() == v)
      {
        heap[i].setDist(newDist);
        heapifyUp(i);
        return;
      }
    }
  }
};

int main()
{
  PriorityQueue<Node> queue;

  queue.insert(Node(1, 10));
  queue.insert(Node(4, 40));
  queue.insert(Node(2, 20));
  queue.insert(Node(5, 50));
  queue.insert(Node(3, 30));

  // Extraindo o máximo
  cout << "Extracted max nodes:" << endl;
  while (!queue.isEmpty())
  {
    Node node = queue.extractMax();
    cout << "Extracted node: " << node.getValue() << ", Dist: " << node.getDist() << endl;
  }
}
