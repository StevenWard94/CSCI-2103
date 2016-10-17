/***************************************************************************//**
 * Author:       Steven Ward <stevenward94@gmail.com>
 * File:         Structures/include/dynamic_stack.h
 * URL:          https://github.com/StevenWard94/csci-2103
 * Last Change:  2016 Oct 17
 ******************************************************************************/

#ifndef STRUCTURES_INCLUDE_DYNAMIC_STACK_H_
#define STRUCTURES_INCLUDE_DYNAMIC_STACK_H_

#include <stddef.h>

template<class T>
class ListStack {
    using value_type = T;
    class node_t;
  public:
    inline bool isEmpty( ) const { return this.top_ == nullptr; }
    inline bool isFull( ) const { return false; }

    size_t size( ) const;
    value_type& top( ) const;
    value_type& pop( );
    ListStack<value_type>& push(value_type const& );

    void clear( );
    //ListStack<value_type>& copy(ListStack<value_type> const& );

    inline ListStack( ) : top_(nullptr), size_(0) { }
    ListStack(ListStack<value_type> const& );
    ~ListStack( );

    ListStack<value_type> const& operator= (ListStack<value_type> const& );

  private:
    node_t* top_;
    size_t size_;
};

#endif  // (STRUCTURES_INCLUDE_DYNAMIC_STACK_H_)
