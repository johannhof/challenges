#include <iostream>
#include <assert.h>

template <class T>
class Node {
  public:
    T* key;
    Node* next;
    ~Node();
};

template <class T>
Node<T>::~Node() {
  delete this->key;
}

template <class T>
class LinkedList {
  Node<T>* head;
  public:
    void insert(T key);
    Node<T>* remove(Node<T>* node);
    Node<T>* operator[](T search);
    LinkedList();
    ~LinkedList();
};

template <class T>
LinkedList<T>::LinkedList() {
  this->head = NULL;
}

template <class T>
LinkedList<T>::~LinkedList() {
  Node<T>* node = this->head;
  while(node != NULL){
    Node<T>* next = node->next;
    delete node;
    node = next;
  }
}

template <class T>
void LinkedList<T>::insert(T key) {
  Node<T>* h = this->head;
  this->head = new Node<T>;
  this->head->key = new T(key);
  this->head->next = h;
}

template <class T>
Node<T>* LinkedList<T>::remove(Node<T>* node) {
  if(this->head == node){
    this->head = node->next;
    return node;
  }
  Node<T>* prev = this->head;
  while(prev != NULL){
    if(prev->next == node){
      prev->next = node->next;
      return node;
    }
    prev = prev->next;
  }

  return NULL;
}


template <class T>
Node<T>* LinkedList<T>::operator[](T search){
  Node<T>* node = this->head;
  while(node != NULL){
    if(*node->key == search){
      return node;
    }
    node = node->next;
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

  delete list.remove(list[3]);
  delete list.remove(list[4]);

  assert(list[3] == NULL);
  assert(list[4] == NULL);

  std::cout << "All tests pass";
}
