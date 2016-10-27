/***********************************************************************************//**
 * Author:       Steven Ward <stevenward94@gmail.com>
 * File:         csci-2103/Structures/include/LinkStack.h
 * URL:          https://github.com/StevenWard94/csci-2103
 * Last Change:  2016 Oct 26
 ***********************************************************************************/

#ifndef STRUCTURES_INCLUDE_LINK_STACK_H_
#define STRUCTURES_INCLUDE_LINK_STACK_H_

#include "stack.h"
#include "basic_node.h"

template<typename T>
class LinkStack : public base::stack<T, base::basic_node> {
    using value_t = typename std::remove_reference<T>::type;
    using node_t = base::basic_node<T>;
    using stack_t = base::stack<T, base::basic_node>;

  public:
    LinkStack& push(value_t const& val) override;
    LinkStack& push(value_t&& val) override;

    LinkStack& pop( ) override;
    value_t&& pop_get( ) override;

    LinkStack& copy( ) const override;
    void clear( ) override;

    LinkStack& operator= (LinkStack const& other) override;
    LinkStack& operator= (LinkStack&& other) override;

    inline LinkStack( ) : stack_t( ) { }
    inline LinkStack(node_t const* top, size_t size) : stack_t(top, size) { }
    inline LinkStack(LinkStack const& other) : stack_t(other) { }
    inline LinkStack(LinkStack&& other) : stack_t(std::move(other)) { }

  private:

};


template<typename T>
LinkStack<T>& LinkStack<T>::push(value_t const& val) {
    node_t const* const pushed = this->top_ptr();
    node_t const* const top = new node_t(val, pushed);
    this->top(top);
    return ++(*this);
}


template<typename T>
LinkStack<T>& LinkStack<T>::push(value_t&& val) {
    node_t const* const pushed = this->top_ptr();
    node_t const* const top = new node_t(std::forward<value_t>(val), pushed);
    this->top(top);
    return ++(*this);
}


template<typename T>
LinkStack<T>& LinkStack<T>::pop( ) {
    node_t* const popped = this->top_ptr();
    node_t const* const top = popped->next;
    this->top(top);
    delete popped;
    return --(*this);
}


template<typename T>
typename std::remove_reference<T>::type&& LinkStack<T>::pop_get( ) {
    value_t popped_val = std::move(this->top());
    this->pop();
    return std::forward<T>(popped_val);
}


template<typename T>
LinkStack<T>& LinkStack<T>::copy( ) const {

    LinkStack<T> copy = LinkStack<T>();

    if (!this->isEmpty()) {
        node_t const* iter = this->top_ptr();
        LinkStack<T> buf = LinkStack<T>();
        while (iter != nullptr) {
            buf.push(iter->data);
            iter = iter->next;
        }
        while (!buf.isEmpty()) {
            copy.push(std::forward<T>(buf.pop_get()));
        }
    }
    return copy;
}


template<typename T>
void LinkStack<T>::clear( ) {
    while (!this->isEmpty()) {
        this->pop();
    }
}


template<typename T>
LinkStack<T>& LinkStack<T>::operator= (LinkStack<T> const& other) {
    if (this != &other) {
        this->size(other->size());
        this->top(nullptr);
        this->top(other->top());
    }
    return *this;
}


template<typename T>
LinkStack<T>& LinkStack<T>::operator= (LinkStack<T>&& other) {
    swap(*this, other);
    return *this;
}

#endif  // (STRUCTURES_INCLUDE_LINK_STACK_H_)
