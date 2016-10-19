/***************************************************************************//**
 * Author:       Steven Ward <stevenward94@gmail.com>
 * File:         <repository-root-dir>/Structures/include/double_link_node.h
 * URL:          https://github.com/StevenWard94/csci-2103
 * Last Change:  2016 Oct 19
 ***************************************************************************/

#ifndef STRUCTURES_INCLUDE_DOUBLE_LINK_NODE_H_
#define STRUCTURES_INCLUDE_DOUBLE_LINK_NODE_H_

#include <stddef.h>

template<class T>
class BiDirectNode {
    using value_type = T;
    using node_type = BiDirectNode<value_type>;

  public:
    inline BiDirectNode(value_type const& data,
                        node_type const* const prev,
                        node_type const* const next)
            : data_(data), prev_(prev), next_(next) { }

    inline BiDirectNode(node_type const& init)
            : data_(init.data()), prev_(init.prev()), next_(init.next()) { }

    inline value_type& data( ) { return this->data_; }
    inline value_type const& data( ) const { return this->data_; }

    inline node_type* prev( ) { return this->prev_; }
    inline node_type const* prev( ) const { return this->prev_; }

    inline node_type* next( ) { return this->next_; }
    inline node_type const* next( ) const { return this->next_; }

  private:
    value_type data_;
    node_type* prev_;
    node_type* next_;
};


#endif  // (STRUCTURES_INCLUDE_DOUBLE_LINK_NODE_H_)
