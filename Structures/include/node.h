/***************************************************************************//**
 * Author:       Steven Ward <stevenward94@gmail.com>
 * File:         <repository-root-dir>/Structures/include/node.h
 * URL:          https://github.com/StevenWard94/csci-2103
 * Last Change:  2016 Oct 18
 ****************************************************************************/

#ifndef STRUCTURES_INCLUDE_NODE_H_
#define STRUCTURES_INCLUDE_NODE_H_

template<class T>
class Node {
    using value_type = T;
  public:
    inline value_type& data( ) const { return this->data_; }
    inline void data(value_type const& data) { this->data_ = data; }
    inline Node<value_type>* next( ) const { return this->next_; }
    inline void next(Node<value_type> const* const node) { this->next_ = node; }

    inline Node(value_type const& data = value_type(),
                Node<value_type> const* const node = nullptr)
            : data_(data), next_(next) { }

    inline Node(Node<value_type> const* const init)
            : Node( init->data(), init->next() ) { }

    inline Node(Node<value_type> const* const init,
                Node<value_type> const* const alt_next)
            : Node( init->data(), alt_next ) { }

  private:
    value_type data_;
    Node<value_type>* next_;

};


#endif  // (STRUCTURES_INCLUDE_NODE_H_)
