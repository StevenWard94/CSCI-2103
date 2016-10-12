/*************************************************************************************//**
 * Steven Ward
 * List.h | String Linked List Program
 *
 * Due Date: October 05, 2016
 ****************************************************************************************/
#ifndef STRING_LIST_LIST_H_
#define STRING_LIST_LIST_H_

#include <stdexcept>
#include <string>

template <typename T>
class List {

public:
  inline List() : nNodes_(0), head_(nullptr) { }

  inline node_t const* head() const { return this->head_; }
  inline size_t length() const { return this->nNodes_; }
  inline bool isEmpty() const { return !this->head_; }

  List<T>& appendNode(T const& node_data);
  List<T>& prependNode(T const& node_data);
  List<T>& insertNode(T const& node_data, size_t index = 0);

  T& at(size_t index);
  T& operator[] (size_t index);
  T const& at(size_t index) const;
  T const& operator[] (size_t index) const;

  T& pop_front();
  T& pop_back();
  List<T>& removeNode(size_t index);
  List<T>& removeData(T const& node_data);

  List<T>& clear();
  ~List();

private:
  struct node_t {
    T data;
    node_t* next;
    inline node_t(T const& data_in, node_t* next_in = nullptr) : data(data_in), next(next_in) { }
  };

  size_t nNodes_;
  node_t* head_;
};


template <typename T>
inline List<T>& List<T>::appendNode(T const& node_data) {
  if (this->head_) {
    node_t* nodeIt = this->head_;
    while (nodeIt->next) {
      nodeIt = nodeIt->next;
    }
    nodeIt->next = new node_t(node_data);
    this->nNodes_++;
  }
  else {
    this->head_ = new node_t(node_data);
  }
  return *this;
}


template <typename T>
inline List<T>& List<T>::prependNode(T const& node_data) {
  if (this->head_) {
    node_t* nodeIt = this->head_;
    this->head_ = new node_t(node_data, nodeIt);
    this->nNodes_++;
  }
  else {
    this->head_ = new node_t(node_data);
    this->nNodes_++;
  }
  return *this;
}


template <typename T>
inline List<T>& List<T>::insertNode(T const& node_data, size_t index/*= 0*/) {
  if (index >= this->nNodes_) {
    throw std::out_of_range("List<T>::insertNode() : 'size_t index' - argument out of range");
  }

  if (index == 0) {
    return prependNode(node_data);
  }
  else if (index == this->nNodes_ - 1) {
    return appendNode(node_data);
  }
  else {
    node_t *nodeIt = this->head_, *prevNode = nullptr;
    for (size_t i = 0; i < index; i++) {
      prevNode = nodeIt;
      nodeIt = prevNode->next;
    }
    prevNode->next = new node_t(node_data, nodeIt);
    this->nNodes_++;
    return *this;
  }
}


template <typename T>
inline T& List<T>::at(size_t index) {
  if (index >= this->nNodes_) {
    throw std::out_of_range("List<T>::at() : 'size_t index' - argument out of range");
  }

  node_t* nodeIt = this->head_;
  for (size_t i = 0; i < index; i++) {
    nodeIt = nodeIt->next;
  }
  return nodeIt->data;
}


template <typename T>
inline T& List<T>::operator[] (size_t index) {
  // no bounds checking with [] operator
  node_t* nodeIt = this->head_;
  for (size_t i = 0; i < index; i++) {
    nodeIt = nodeIt->next;
  }
  return nodeIt->data;
}


template <typename T>
inline T& List<T>::pop_front() {
  if (this->isEmpty()) {
    throw std::domain_error("List<T>::pop_front() : member function undefined for empty instances");
  }
  else if (this->head_->next == nullptr) {
    node_t* nodeIt = this->head_;
    this->head_ = nullptr;
  }
  else {
    node_t* nodeIt = this->head_;
    this->head_ = nodeIt->next;
  }
  this->nNodes_--;
  return nodeIt->data;
}


template <typename T>
inline T& List<T>::pop_back() {
  if (this->isEmpty()) {
    throw std::domain_error("List<T>::pop_back() : member function undefined for empty instances");
  }
  else if (this->head_->next == nullptr) {
    node_t* pop = this->head_;
    this->head_ = nullptr;
  }
  else {
    node_t* nodeIt = this->head_;
    while (nodeIt->next->next) {
      nodeIt = nodeIt->next;
    }
    node_t* pop = nodeIt->next;
    nodeIt->next = nullptr;
  }
  this->nNodes_--;
  return pop->data;
}


template <typename T>
inline List<T>& List<T>::removeNode(size_t index) {
  if (index >= this->nNodes_) {
    throw std::out_of_range("List<T>::removeNode() : 'size_t index' - argument out of range");
  }
  else if (index == 0) {
    node_t* remove = this->head_;
    this->head_ = remove->next;
  }
  else {
    node_t *remove = this->head_, *prevNode = nullptr;
    for (size_t i = 0; i < index; i++) {
      prevNode = remove;
      remove = prevNode->next;
    }
    prevNode->next = remove->next;
  }
  delete remove;
  remove = nullptr;
  this->nNodes--;
  return *this;
}


template <typename T>
inline List<T>& List<T>::removeData(T const& node_data) {
  node_t *nodeIt = this->head, *prevNode = nullptr;
  while (nodeIt && nodeIt->data != node_data) {
    prevNode = nodeIt;
    nodeIt = prevNode->next;
  }
  if (nodeIt) {
    prevNode->next = nodeIt->next;
    delete nodeIt;
    nodeIt = nullptr;
    this->nNodes_--;
  }
  return *this;
}


template <typename T>
inline List<T>& List<T>::clear() {
  if ( !this->isEmpty() ) {
    node_t* annihilator = this->head_;
    node_t* nodeIt = annihilator->next;

    while (annihilator != nullptr && this->nNodes_ != 0) {
      delete annihilator;
      this->nNodes_--;
      annihilator = nodeIt;
      nodeIt = nodeIt ? annihilator->next : nullptr;
    }
    this->head_ = nullptr;
  }
  return *this;
}


template <typename T>
inline List<T>::~List() {
  this->clear();
}

template<>
class List<std::string>;
#endif  // STRING_LIST_LIST_H_
