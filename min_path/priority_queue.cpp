#include <iostream>
#include <vector>
using namespace std;

typedef int Key;
typedef string Value;
typedef unsigned int uint;

class Data
{
private:
  Key key;
  Value value;

public:
  Data() : key(0), value("") {}
  Data(Key key, Value value) : key(key), value(value) {}
  void print() const { cout << "key: " << key << ", value: " << value << endl; }
  Key getKey() const { return key; }
  void setKey(Key newKey) { key = newKey; }
  Value getValue() const { return value; }
  void setValue(Value newValue) { value = newValue; }
};

template <typename T>
class MaxBinaryHeap
{
private:
  vector<T> heap;
  uint len;

public:
  MaxBinaryHeap(uint MAX_SIZE) : len(0)
  {
    heap.reserve(MAX_SIZE);
  }
  bool isEmpty() const
  {
    return heap.empty();
  }
  void insert(T data)
  {
    heap.push_back(data);
    uint index = heap.size() - 1;
    while (index > 0)
    {
      uint parentIndex = (index - 1) / 2;
      if (heap[parentIndex].getKey() >= heap[index].getKey())
        break;
      swap(heap[index], heap[parentIndex]);
      index = parentIndex;
    }
  }
  T popMax()
  {
    if (heap.empty())
      throw runtime_error("Heap is empty");
    T max = heap[0];
    heap[0] = heap.back();
    heap.pop_back();
    uint index = 0;
    while (true)
    {
      uint left = 2 * index + 1;
      uint right = 2 * index + 2;
      uint largest = index;
      if (left < heap.size() && heap[left].getKey() > heap[largest].getKey())
        largest = left;
      if (right < heap.size() && heap[right].getKey() > heap[largest].getKey())
        largest = right;
      if (largest == index)
        break;
      swap(heap[index], heap[largest]);
      index = largest;
    }
    return max;
  }
  T getMax()
  {
    if (heap.empty())
      throw runtime_error("Heap is empty");
    return heap[0];
  }
  void updateKey(T data, int newKey)
  {
    for (int i = 0; i < heap.size(); ++i)
    {
      if (heap[i].getKey() == data.getKey())
      {
        heap[i].setKey(newKey);
        while (i > 0)
        {
          int parentIndex = (i - 1) / 2;
          if (heap[parentIndex].getKey() >= heap[i].getKey())
            break;
          swap(heap[i], heap[parentIndex]);
          i = parentIndex;
        }
        return;
      }
    }
    throw runtime_error("Item not found in heap");
  }
  void printHeap() const
  {
    for (const auto &item : heap)
      item.print();
    cout << endl;
  }
};

int main()
{
  Data data1(1, "apple");
  Data data2(2, "banana");
  Data data3(3, "pizza");
  Data data4(4, "sushi");
  Data data5(5, "tacos");
  Data data6(6, "ice cream");
  Data data7(7, "chocolate");
  Data data8(8, "coffee");
  Data data9(9, "tea");
  Data data10(10, "milk");
  MaxBinaryHeap<Data> maxHeap(10);
  maxHeap.insert(data1);
  maxHeap.insert(data2);
  maxHeap.insert(data3);
  maxHeap.insert(data4);
  maxHeap.insert(data5);
  maxHeap.insert(data6);
  maxHeap.insert(data7);
  maxHeap.insert(data8);
  maxHeap.insert(data9);
  maxHeap.insert(data10);
  maxHeap.printHeap();
  cout << "Extracting max element from heap..." << endl;
  Data maxElement = maxHeap.popMax();
  cout << "Max element extracted: ";
  maxElement.print();
  cout << "Heap after extraction:" << endl;
  maxHeap.printHeap();

  cout << "Updating key of element with value 'banana' to 20..." << endl;
  maxHeap.updateKey(data7, 20);
  cout << "Heap after update:" << endl;
  maxHeap.printHeap();

  cout << "Extracting max element from heap again..." << endl;
  maxElement = maxHeap.popMax();
  cout << "Max element extracted: ";
  maxElement.print();
  cout << "Heap after second extraction:" << endl;
  maxHeap.printHeap();

  cout << "Checking if heap is empty..." << endl;
  if (maxHeap.isEmpty())
    cout << "Heap is empty." << endl;
  else
    cout << "Heap is not empty." << endl;
}