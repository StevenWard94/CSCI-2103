/***********************************************************************************//**
 * Author:        Steven Ward <stevenward94@gmail.com>
 * Project:       LinkedList
 * File:          include/LinkedList.cpp
 * Last Change:   2016 Oct 04
 **************************************************************************************/

#include "LinkedList.h"

#include <stdexcept>

using NodeType = LinkedList<T>::NodeType;

static const std::size_t npos = -1;

template <class T>
LinkedList<T>::LinkedList<T>(const NodeType* head) : this() {
  this->head_ = head;
  NodeType* nodeIt = this->head_;
  while (nodeIt) {
    this->nNodes_++;
    nodeIt = nodeIt->next;
  }
}


template <class T>
LinkedList<T>::LinkedList<T>(const T& data) : this() {
  NodeType* head = new NodeType(data);
  this->head_ = head;
}


template <class T, class InputIterator>
LinkedList<T>::LinkedList<T>(InputIterator first, InputIterator last) : this() {
  if (first == last || first = nullptr) {
    return;
  }
  this->head_ = new NodeType(*first);
  NodeType *nodeIt = this->head_, *prevNode = nullptr;
  this->nNodes_++;

  for (InputIterator it = first + 1; it != last; it++) {
    prevNode = nodeIt;
    nodeIt = new NodeType(*it);
    prevNode->next = nodeIt;
    this->nNodes_++;
  }
}


template <class T>
NodeType* LinkedList<T>::head(const NodeType* head) {
  NodeType* oldHead = this->head_;
  if (head != nullptr) {
    this->head_ = new NodeType(head->data, oldHead->next);
  }
  return oldHead;
}


template <class T>
LinkedList<T>& LinkedList<T>::appendNode(const T& data) {
  if ( this->isEmpty() ) {
    this->head_ = new NodeType(data);
    this->nNodes_++;
  }
  else {
    NodeType* nodeIt = this->head_;
    while ( nodeIt->next ) {
      nodeIt = nodeIt->next;
    }
    nodeIt->next = new NodeType(data);
    this->nNodes_++;
  }
  return *this;
}


template <class T>
LinkedList<T>& LinkedList<T>::prependNode(const T& data) {
  if ( this->isEmpty() ) {
    this->head_ = new NodeType(data);
    this->nNodes_++;
  }
  else {
    this->head_ = new NodeType(data, this->head_);
    this->nNodes_++;
  }
  return *this;
}


template <class T>
LinkedList<T>& LinkedList<T>::insertNode(const T& data, const std::size_t index) {
  if (index >= this->nNodes_) {
    return this->appendNode(data);
  }
  else if (index == 0) {
    return this->prependNode(data);
  }
  else {
    NodeType *preNode = nullptr;
    NodeType *postNode = this->head_;

    for (std::size_t i = 0; i < index; i++) {
      preNode = postNode;         // at end of iteration n, preNode points to node n.
      postNode = postNode->next;  // at end of iteration n, postNode points to node n+1.
    }
    preNode->next = new NodeType(data, postNode);
    this->nNodes_++;
  }
}


template <class T>
std::size_t LinkedList<T>::find(const T& value, const std::size_t pos/*= 0*/) const {
  if (pos >= this->nNodes_) {
    throw std::out_of_range("LinkedList<T>::find() : const std::size_t pos out of range");
  }

  const NodeType* nodeIt = this->head_;
  std::size_t index = 0;
  if (pos > 0) {
    for (std::size_t i = 0; i < pos + 1; i++) {
      nodeIt = nodeIt->next;
      index++;
    }
  }
  while (nodeIt) {
    if (nodeIt->data == value) {
      return index;
    }
    else {
      nodeIt = nodeIt->next;
      index++;
    }
  }
  return LinkedList<T>::npos
}


template <class T>
std::size_t LinkedList<T>::count(const T& value, const std::size_t pos/*= 0*/) const {
  if (pos >= this->nNodes_) {
    throw std::out_of_range("LinkedList<T>::count() : const std::size_t pos out of range")
  }

  const NodeType* nodeIt = this->head_;
  std::size_t count = 0;
  if (pos > 0) {
    for (std::size_t i = 0; i < pos + 1; i++) {
      nodeIt = nodeIt->next;
    }
  }
  while (nodeIt) {
    count += (nodeIt->data == value) ? 1 : 0;
    nodeIt = nodeIt->next;
  }
  return count;
}


template <class T>
T& LinkedList<T>::at(const std::size_t index) {
  if (index >= this->nNodes_) {
    throw std::out_of_range("LinkedList<T>::at : const std::size_t index out of range");
  }
  const NodeType* nodeIt = this->head_;
  for (std::size_t i = 0; i < index + 1; i++) {
    nodeIt = nodeIt->next;
  }
  return nodeIt->data;
}


template <class T>
T& LinkedList<T>::operator[] (const std::size_t index) {
  return this->at(index);
}
