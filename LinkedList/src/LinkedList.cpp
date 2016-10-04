/***********************************************************************************//**
 * Author:        Steven Ward <stevenward94@gmail.com>
 * Project:       LinkedList
 * File:          include/LinkedList.cpp
 * Last Change:   2016 Oct 04
 **************************************************************************************/

#include "LinkedList.h"

#include <stdexcept>

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


template <class T>
NodeType* LinkedList<T>::head(const NodeType* head) {
  NodeType* oldHead = this.head_;
  if (head != nullptr) {
    this.head_ = new NodeType(head->data, oldHead->next);
  }
  return oldHead;
}


template <class T>
LinkedList<T>& LinkedList<T>::appendNode(const T& data) {
  if ( this.isEmpty() ) {
    this.head_ = new NodeType(data);
    this.nNodes_++;
  }
  else {
    NodeType* nodeIt = this.head_;
    while ( nodeIt->next ) {
      nodeIt = nodeIt->next;
    }
    nodeIt->next = new NodeType(data);
    this.nNodes_++;
  }
  return *this;
}


template <class T>
LinkedList<T>& LinkedList<T>::prependNode(const T& data) {
  if ( this.isEmpty() ) {
    this.head_ = new NodeType(data);
    this.nNodes_++;
  }
  else {
    this.head_ = new NodeType(data, this.head_);
    this.nNodes_++;
  }
  return *this;
}


template <class T>
LinkedList<T>& LinkedList<T>::insertNode(const T& data, const std::size_t index) {

}
