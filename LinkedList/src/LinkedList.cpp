/***********************************************************************************//**
 * Author:        Steven Ward <stevenward94@gmail.com>
 * Project:       LinkedList
 * File:          include/LinkedList.cpp
 * Last Change:   2016 Oct 04
 **************************************************************************************/

#include "LinkedList.h"

using NodeType = LinkedList<T>::NodeType;

template <class T>
LinkedList<T>::LinkedList<T>(const NodeType* head) : this() {
  this.head_ = head;
  NodeType* nodeIt = this.head_;
  while (nodeIt) {
    this.nNodes_++;
    nodeIt = nodeIt->next;
  }
}


template <class T>
LinkedList<T>::LinkedList<T>(const T& data) : this() {
  NodeType* head = new NodeType(data);
  this.head_ = head;
}


template <class T, class InputIterator>
LinkedList<T>::LinkedList<T>(InputIterator first, InputIterator last) : this() {
  if (first == last || first = nullptr) {
    return;
  }
  this.head_ = new NodeType(*first);
  NodeType *nodeIt = this.head_, *prevNode = nullptr;
  this.nNodes_++;

  for (InputIterator it = first + 1; it != last; it++) {
    prevNode = nodeIt;
    nodeIt = new NodeType(*it);
    prevNode->next = nodeIt;
    this.nNodes_++;
  }
}
