/***************************************************************************//**
 * file:          <project-root-dir>/src/SingleLinkList.cpp
 * author:        Steven Ward <stevenward94@gmail.com>
 * url:           https://github.com/StevenWard94/csci-2103.git
 * last change:   2016 Oct 11
****************************************************************************/

#ifndef SRC_SINGLE_LINK_LIST_CPP_
#define SRC_SINGLE_LINK_LIST_CPP_

#include <iostream>

#include <stddef.h>

namespace linked_lists {

template <class T>
class List {
  class Node_t;
 public:
  static const size_t NPOS = -1;

  /** inline accessor functions for private instance members */
  inline Node_t* head( ) const { return this->head_; }
  inline Node_t* tail( ) const { return this->tail_; }
  inline size_t  size( ) const { return this->size_; }

  inline bool isEmpty( ) const {
    return ( this->size_ == 0 && !this->head_ && !this->tail_ );
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
  List<T>& erase(size_t first_incl = 0, size_t last_excl = NPOS);

  inline List( ) : head_(nullptr), tail_(nullptr), size_(0) { }
  List(T const& data);
  List(Node_t const* first_node);
  // TODO: DEFINE MORE CONSTRUCTORS
  ~List( );

 private:
  Node_t* head_;
  Node_t* tail_;
  size_t  size_;
};
}

#endif    // (SRC_SINGLE_LINK_LIST_CPP_)

namespace linked_lists {
// TODO: implementation for List<T> class
}
