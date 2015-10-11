/*
10.2-8
Explain how to implement doubly linked lists using only one pointer value
x:np per item instead of the usual two (next and pre􏰁). Assume that all pointer
values can be interpreted as k-bit integers, and define x:np to be x:np D x:next XOR x:pre,
the k-bit “exclusive-or” of x:next and x:pre􏰁. (The value NIL is represented by 0.)
Be sure to describe what information you need to access the head of the list.
Show how to implement the SEARCH, INSERT, and DELETE operations on such a list.
Also show how to reverse such a list in O.1/ time.
*/

#include <iostream>
#include <assert.h>

template <class T>
class Node {
  public:
    T* key;
    uintptr_t np;
    ~Node();
};

template <class T>
Node<T>::~Node() {
  delete this->key;
}

template <class T>
class LinkedList {
  public:
    Node<T>* head;
    void insert(T key);
    Node<T>* remove(Node<T>* n);
    Node<T>* operator[](T search);
    LinkedList();
    ~LinkedList();
};

template <class T>
std::ostream &operator<<(std::ostream &os, LinkedList<T> const &list) {
  uintptr_t prev = 0;
  Node<T>* node = list.head;
  while(node != NULL){
    os << *node->key << " " << node->np << std::endl;
    uintptr_t prev_node = (uintptr_t) node;
    node = (Node<T>*)(node->np ^ prev);
    prev = prev_node;
  }
  return os;
}

template <class T>
LinkedList<T>::LinkedList() {
  this->head = NULL;
}

template <class T>
LinkedList<T>::~LinkedList() {
  uintptr_t prev = 0;
  Node<T>* node = this->head;
  while(node != NULL){
    uintptr_t prev_node = (uintptr_t) node;
    node = (Node<T>*)(node->np ^ prev);
    prev = prev_node;
    delete (Node<T>*) prev_node;
  }
}

template <class T>
void LinkedList<T>::insert(T key) {
  Node<T>* node = new Node<T>;
  node->np = (uintptr_t) this->head;
  node->key = new T(key);
  if(this->head != 0){
    this->head->np = (uintptr_t) node ^ this->head->np;
  }
  this->head = node;
}

template <class T>
Node<T>* LinkedList<T>::remove(Node<T>* n) {
  if(n == this->head){
    Node<T>* next = (Node<T>*) n->np;
    this->head = next;
    uintptr_t next_next = next->np ^ (uintptr_t) n;
    next->np = next_next;
    return n;
  }

  uintptr_t prev = 0;
  Node<T>* node = this->head;
  while(node != NULL){
    Node<T>* prev_node = node;
    node = (Node<T>*)(node->np ^ prev);
    if(node == n){
      uintptr_t next = node->np ^ (uintptr_t) prev_node;
      prev_node->np = prev ^ next;
      uintptr_t next_next = ((Node<T>*)next)->np ^ (uintptr_t) node;
      ((Node<T>*)next)->np = next_next ^ (uintptr_t) prev_node;
      return node;
    }
    prev = (uintptr_t) prev_node;
  }

  return NULL;
}


template <class T>
Node<T>* LinkedList<T>::operator[](T search){
  uintptr_t prev = 0;
  Node<T>* node = this->head;
  while(node != NULL){
    if(*node->key == search){
      return node;
    }
    uintptr_t prev_node = (uintptr_t) node;
    node = (Node<T>*)(node->np ^ prev);
    prev = prev_node;
  }
  return NULL;
}

int main() {
  LinkedList<int> list;
  list.insert(5);
  list.insert(8);
  list.insert(3);
  list.insert(4);

  assert(*list[8]->key == 8);
  assert(*list[5]->key == 5);
  assert(*list[3]->key == 3);
  assert(list[20] == NULL);

  delete list.remove(list[8]);
  delete list.remove(list[4]);

  assert(list[8] == NULL);
  assert(list[4] == NULL);

  std::cout << "All tests pass";
}
