/***************************************************************************//**
 * file:          <project-root-dir>/src/SingleLinkList.cpp
 * author:        Steven Ward <stevenward94@gmail.com>
 * url:           https://github.com/StevenWard94/csci-2103.git
 * last change:   2016 Oct 12
****************************************************************************/

#ifndef SRC_SINGLE_LINK_LIST_CPP_
#define SRC_SINGLE_LINK_LIST_CPP_

#include <iostream>
#include <utility>

#include <stddef.h>

namespace single_link {

template<class T>
class List {
  class node_t;
 public:
  static const size_t NPOS = -1;

  /** inline accessor functions for private instance members */
  inline node_t* head( ) const { return this->head_; }
  inline node_t* tail( )  const { return this->tail_; }
  inline size_t  size( ) const { return this->size_; }

  inline bool isEmpty( ) const {
    return ( this->size_ == 0 && this->head_ == nullptr );
  }

  List<T>& append(T const& data);
  List<T>& prepend(T const& data);
  List<T>& insert(T const& data, size_t index);

  size_t find(T const& data, size_t pos = 0) const;
  T& at(size_t index);
  T const& at(size_t index) const;
  T& operator[](size_t index);
  T const& operator[](size_t index) const;
  bool contains(T const& data);

  List<T>& assign(size_t index, T const& new_data);
  List<T>& replace(T const& old_data, T const& new_data, size_t n = 1);
  List<T>& replaceAll(T const& old_data, T const& new_data);
  List<T>& replaceAll(size_t begin, size_t end, T const& old_data, T const& new_data);

  List<T>& remove(size_t index);
  List<T>& remove(T const& data, size_t n = 1, size_t pos = 0);
  List<T>& removeAll(T const& data, size_t pos = 0);
  List<T>& erase(size_t first = 0, size_t last = NPOS);

  inline List( ) : head_(nullptr), tail_(nullptr), size_(0) { }
  List(T const& data, node_t* init_elem = nullptr);
  List(size_t init_size, T const& init_data = T());
  List(List<T> const& init);
  template<class InputIterator>
  List(InputIterator first, InputIterator last);
  ~List( );

  List<T>& operator=(List<T> rhs_copy);
  void swap(List<T>& rhs) noexcept;

 private:
  node_t* head_;
  node_t* tail_;
  size_t  size_;

  template<class U> friend std::ostream& operator<<(std::ostream& , List<U> const& );
  template<class U> friend std::istream& operator>>(std::istream& , List<U>& );

};

template<class T>
class node_t {
 public:
  T data;
  node_t* next;

  node_t(T const& init_data = T(), node_t* const init_next = nullptr)
    : data(init_data), next(init_next) { }

  node_t(node_t const* const init, node_t* const init_next = nullptr)
    : data(init->data), next(init_next) { }
};




template<class T>
List<T>& List<T>::append(T const& data) {
  if (!isEmpty()) {
    node_t* nodeIt = this->head_;
    while (nodeIt->next != this->tail_) {
      nodeIt = nodeIt->next;
    }
    nodeIt->next = new node_t(data, this->tail_);
  }
  else {
    this->head_ = new node_t(data, this->tail_);
  }
  this->size_++;
  return *this;
}


template<class T>
List<T>& List<T>::prepend(T const& data) {
  if (!isEmpty()) {
    node_t* oldHead = this->head_;
    this->head_ = new node_t(data, oldHead);
  }
  else {
    this->head_ = new node_t(data, this->tail_);
  }
  this->size_++;
  return *this;
}


template<class T>
List<T>& List<T>::insert(T const& data, size_t index) {
  if (index == 0) {
    return this->prepend(data);
  }
  else if (index == this->size_) {
    return this->append(data);
  }
  else if (index > this->size_) {
    throw std::out_of_range("List<T>::insert() : arg 2, 'size_t index' out of range");
  }
  else {
    node_t* nodeIt = this->head_;
    node_t* prevNode = nullptr;
    for (size_t i = 0; i < index; i++) {
      prevNode = nodeIt;
      nodeIt = nodeIt->next;
    }
    prevNode->next = new node_t(data, nodeIt);
    this->size_++;
  }
  return *this;
}
}

#endif    // (SRC_SINGLE_LINK_LIST_CPP_)