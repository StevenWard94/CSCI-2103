/***********************************************************************************//**
 * Author:       Steven Ward <stevenward94@gmail.com>
 * File:         csci-2103/LinkedLists/src/List.cpp
 * URL:          https://github.com/StevenWard94/csci-2103
 * Last Change:  2016 Oct 12
 ***********************************************************************************/

#include <iostream>
#include <stdexcept>
#include <string>
#include <utility>

#include <stdlib.h>

// Begin definition of List class template
template<typename T>
class List {
    using value_t = T;
    struct Node;

  public:
    inline Node const* head( ) const { return head_; }
    inline Node const* tail( ) const { return tail_; }
    inline size_t size( ) const { return size_; }

    inline value_t front( ) const { return std::forward<value_t>(head_->data); }
    inline value_t back( ) const { return std::forward<value_t>(tail_->data); }
    inline bool isEmpty( ) const { return head_ == nullptr; }

    List<T>& append(value_t const& val);
    List<T>& append(value_t&& val);
    List<T>& prepend(value_t const& val);
    List<T>& prepend(value_t&& val);
    List<T>& insert(value_t const& val, size_t pos);
    List<T>& insert(value_t&& val, size_t pos);

    size_t find(value_t const& val, size_t pos = 0) const;
    size_t find(value_t&& val, size_t pos = 0) const;

    value_t& at(size_t index);
    value_t const& at(size_t index) const;
    value_t& operator[](size_t index);
    value_t const& operator[](size_t index) const;

    bool remove(value_t const& val);
    bool remove(value_t&& val);
    value_t removeAt(size_t index);

    List<T>& operator= (List<T> const& rhs);

    List( ) = default;
    List(List const& other);
    List(List&& other);

  private:
    Node* head_{ nullptr };
    Node* tail_{ nullptr };
    size_t size_{ 0 };

    struct Node {
        value_t data{ value_t() };
        Node* next{ nullptr };

        Node( ) = default;
        Node(value_t const& val) : data{ new value_t(val) } { }
        Node(value_t&& val) : data{ std::move(val) } { }

        Node(Node const& other)
                : data{ new value_t(other.data) }, next{ new Node(*other.next) } { }

        Node(Node&& other)
                : data{ std::move(other.data) }, next{ std::move(other.next) }
        { other.next = nullptr; }

    };

};
