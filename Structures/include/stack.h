/***********************************************************************************//**
 * Author:       Steven Ward <stevenward94@gmail.com>
 * File:         csci-2103/Structures/include/stack.h
 * URL:          https://github.com/StevenWard94/csci-2103
 * Last Change:  2016 Oct 26
 ***********************************************************************************/

#ifndef STRUCTURES_INCLUDE_BASE_STACK_H_
#define STRUCTURES_INCLUDE_BASE_STACK_H_

#include <type_traits>
#include <utility>

#include <stddef.h>

namespace base {

template<typename T, template<typename> class Node>
class stack {
    using value_t = typename std::remove_reference<T>::type;
    using node_t = Node<T>;
    using stack_t = typename std::remove_reference<stack<T, Node>>::type;

  public:
    inline value_t const& top( ) const { return top_; }
    inline size_t size( ) const { return size_; }

    inline bool isEmpty( ) const { return top_ == nullptr; }
    inline constexpr bool isFull( ) const { return false; }

    virtual stack_t& push(value_t const& ) = 0;
    virtual stack_t& push(value_t&& ) = 0;

    virtual stack_t& pop( ) = 0;
    virtual value_t&& pop_get( ) = 0;

    virtual stack_t& copy( ) const = 0;
    virtual void clear( ) = 0;

    virtual stack_t& operator=(stack const& ) = 0;
    virtual stack_t& operator=(stack&& ) = 0;

  protected:
    inline stack(node_t const* top = nullptr, size_t size = 0)
            : top_(std::forward<Node>(*top)), size_(size) { }

    inline stack(stack const& other)
            : top_(*other.top_), size_(other.size_) { }

    inline stack(stack&& other)
            : top_(std::forward<Node>(*other.top_)), size_(std::move(other.size_))
    {
        other.top_ = nullptr;
        other.size_ = size_t();
    }

    inline void top(node_t const* node) { this.top_ = node; }
    inline node_t* top_ptr( ) const { return this->top_; }
    inline void size(size_t size) { this.size_ = size; }

    template<typename Ptr, typename = typename std::enable_if<std::is_null_pointer<Ptr>::value>>
    inline void top(Ptr np) {
        this->clear();
        delete this->top_;
        this->top_ = nullptr;
    }

    inline stack_t& operator++( ) {
        ++size_;
        return *this;
    }

    inline stack_t& operator--( ) {
        size_ -= size_ == 0 ? 0 : 1;
        return *this;
    }

    inline stack_t operator++(int) {
        stack_t tmp = *this;
        ++(*this);
        return tmp;
    }

    inline stack_t operator--(int) {
        stack_t tmp = *this;
        --(*this);
        return tmp;
    }

  private:
    node_t* top_;
    size_t size_;

  friend void swap(stack_t lhs, stack_t rhs) {
      std::swap(lhs.top_, rhs.top_);
      std::swap(lhs.size_, rhs.size_);
  }
};

}  /* end namespace base */


#endif  // (STRUCTURES_INCLUDE_BASE_STACK_H_)
