/***********************************************************************************//**
 * Author:       Steven Ward <stevenward94@gmail.com>
 * File:         csci-2103/Structures/include/stack.h
 * URL:          https://github.com/StevenWard94/csci-2103
 * Last Change:  2016 Oct 26
 ***********************************************************************************/

#ifndef STRUCTURES_INCLUDE_BASE_STACK_H_
#define STRUCTURES_INCLUDE_BASE_STACK_H_

#include <utility>
#include <stddef.h>

namespace base {

template<typename T, template<typename> class Node>
class stack {
    using value_t = T;
    using node_t = Node<T>;

  public:
    inline value_t const& top( ) const { return top_; }
    inline size_t size( ) const { return size_; }

  protected:
    inline stack(node_t const* const top = nullptr, size_t size = 0)
            : top_(top), size_(size) { }

    inline stack(stack const& other) : top_(*other.top_), size_(other.size_) { }

    inline stack(stack&& other)
            : top_(std::move(*other.top_)), size_(std::move(other.size_))
    {
        other.top_ = nullptr;
        other.size_ = size_t();
    }

    inline void top(node_t const* const node) { this.top_ = new node_t(node); }
    inline void size(size_t size) { this.size_ = size; }

  private:
    node_t* top_;
    size_t size_;
};

}  /* end namespace base */


#endif  // (STRUCTURES_INCLUDE_BASE_STACK_H_)
