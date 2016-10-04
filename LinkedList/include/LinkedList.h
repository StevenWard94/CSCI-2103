/***********************************************************************************//**
 * Author:        Steven Ward <stevenward94@gmail.com>
 * Project:       LinkedList
 * File:          include/LinkedList.h
 * Last Change:   2016 Sep 30
 **************************************************************************************/

#ifndef INCLUDE_LINKEDLIST_H_
#define INCLUDE_LINKEDLIST_H_

// #include <iterator>

template <class T>
class LinkedList {

private:
  struct NodeType {
    T data;
    NodeType* next;
    NodeType(const T& t, const NodeType* node = nullptr) : this.data(t), this.next(node) { }
    NodeType(const NodeType& init, const NodeType* node = nullptr) : this(init.data, node) { }
  };

  NodeType* head_;
  std::size_t nNodes_;

public:
  inline NodeType* head() const { return head_; }
  NodeType* head(const NodeType* head);

  inline std::size_t size() const { return nNodes_; }
  inline bool isEmpty() const { return !head_; }

  LinkedList<T>& appendNode(const T& data);
  LinkedList<T>& prependNode(const T& data);
  LinkedList<T>& insertNode(const T& data, const std::size_t index);

  LinkedList<T>& replaceNode(const T& newData, const T& old, const std::size_t pos = 0);
  LinkedList<T>& replaceNodeAt(const T& data, const std::size_t index);

  LinkedList<T>& deleteNode(const T& data);
  LinkedList<T>& deleteNode(const std::size_t index);

  std::size_t find(const T& value, const std::size_t pos = 0) const;
  std::size_t count(const T& value, const std::size_t pos = 0) const;
  T& at(const std::size_t index) const;
  NodeType& operator[] (std::size_t index);

  inline LinkedList<T>() : nNodes_(0), head_(nullptr) { }
  LinkedList<T>(const NodeType* head);
  LinkedList<T>(const T& data);

  template <class InputIterator>
  LinkedList<T>(InputIterator first, InputIterator last);

  ~LinkedList<T>();

};

#endif  // INCLUDE_LINKEDLIST_H_
