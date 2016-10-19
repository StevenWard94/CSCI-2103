/***************************************************************************//**
 * Author:       Steven Ward <stevenward94@gmail.com>
 * File:         <repository-root-dir>/Structures/include/node.h
 * URL:          https://github.com/StevenWard94/csci-2103
 * Last Change:  2016 Oct 18
 ******************************************************************************/

#ifndef STRUCTURES_INCLUDE_NODE_H_
#define STRUCTURES_INCLUDE_NODE_H_

template<class T>
class Node {
    using data_type = T;
  public:
    inline data_type& data( ) const { return this->data_; }
    inline void data(data_type const& data) { this->data_ = data; }
    inline Node<data_type>* next( ) const { return this->next_; }
    inline void next(Node<data_type> const* const node) { this->next_ = node; }

    inline Node(data_type const& data = data_type(),
                Node<data_type> const* const node = nullptr)
            : data_(data), next_(next) { }

    inline Node(Node<data_type> const* const init)
            : Node( init->data(), init->next() ) { }

    inline Node(Node<data_type> const* const init,
                Node<data_type> const* const alt_next)
            : Node( init->data(), alt_next ) { }

  private:
    data_type data_;
    Node<data_type>* next_;
};

/*
template<class T>
inline bool operator==(Node<T> const& lhs, Node<T> const& rhs) {
    return lhs.data() == rhs.data();
}

template<class T>
inline bool operator!=(Node<T> const& lhs, Node<T> const& rhs) {
    return !operator==(lhs,rhs);
}

template<class T>
inline bool operator< (Node<T> const& lhs, Node<T> const& rhs) {
    return lhs.data() < rhs.data();
}

template<class T>
inline bool operator> (Node<T> const& lhs, Node<T> const& rhs) {
    return operator< (rhs,lhs);
}

template<class T>
inline bool operator<=(Node<T> const& lhs, Node<T> const& rhs) {
    return !operator> (lhs,rhs);
}

template<class T>
inline bool operator>=(Node<T> const& lhs, Node<T> const& rhs) {
    return !operator< (lhs,rhs);
}
*/

#endif  // (STRUCTURES_INCLUDE_NODE_H_)
