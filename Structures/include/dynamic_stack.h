/***************************************************************************//**
 * Author:       Steven Ward <stevenward94@gmail.com>
 * File:         Structures/include/dynamic_stack.h
 * URL:          https://github.com/StevenWard94/csci-2103
 * Last Change:  2016 Oct 17
 ******************************************************************************/

#ifndef STRUCTURES_INCLUDE_STACKS_DYNAMIC_STACK_H_
#define STRUCTURES_INCLUDE_STACKS_DYNAMIC_STACK_H_

#include <stdexcept>

#include <stddef.h>

namespace stacks {

template<class E>
class ListStack {
    using value_type = E;
    class node_t;
  public:
    inline bool isEmpty( ) const { return this->top_ == nullptr; }
    inline bool isFull( ) const { return false; }

    inline node_t const* const top_intern( ) const { return this->top_; }
    size_t size( ) const { return this->size_; }

    value_type& top( ) const;
    ListStack<value_type>& pop( );
    ListStack<value_type>& push(value_type const& );

    ListStack<value_type>& clear( );
    ListStack<value_type>& copy(ListStack<value_type> const& );

    inline ListStack( ) : top_(nullptr), size_(0) { }
    ListStack(ListStack<value_type> const& );
    ~ListStack( );

    ListStack<value_type>& operator= (ListStack<value_type> const& );

  private:
    node_t* top_;
    size_t size_;
};
// end definition of 'ListStack<E>' class


// begin implementation of 'ListStack<E>' class

template<class E>
class ListStack<E>::node_t {
  public:
    value_type data;
    node_t* next;

    node_t( value_type const& init_data = value_type(),
            node_t* const init_next = nullptr )
          : data(init_data), next(init_next) { }
};


template<class E>
inline E& ListStack<E>::top( ) const { return this->top_->data; }


template<class E>
inline ListStack<E>& ListStack<E>::pop( ) {
    node_t* popped = nullptr;
    if (!this->isEmpty()) {
        popped = this->top_;
        this->top_ = popped->next;
        this->size_--;
        delete popped;
    }
    return *this;
}


template<class E>
inline ListStack<E>& ListStack<E>::push(value_type const& elem) {
    if (!this->isEmpty()) {
        node_t* pushed = this->top_;
        this->top_ = new node_t(elem, pushed);
        this->size_++;
    }
    else {
        this->top_ = new node_t(elem);
        this->size_++;
    }
    return *this;
}


template<class E>
inline ListStack<E>& ListStack<E>::clear( ) {
    while (!this->isEmpty()) {
        this->pop();
    }
    this->size_ = 0;
    this->top_ = nullptr;

    return *this;
}


template<class E>
inline ListStack<E>& ListStack<E>::copy(ListStack<E> const& init) {
    if (!this->isEmpty()) {
        this->clear();
    }
    node_t const* nodeIt = init.top_intern();
    while (nodeIt != nullptr) {
        this->push(nodeIt->data);
        nodeIt = nodeIt->next;
    }
    return *this;
}
// TODO: IMPLEMENTATION FOR CONSTRUCTORS, DESTRUCTOR & ASSIGNMENT OPERATOR


}  // end 'stacks' namespace

#endif  // (STRUCTURES_INCLUDE_STACKS_DYNAMIC_STACK_H_)
