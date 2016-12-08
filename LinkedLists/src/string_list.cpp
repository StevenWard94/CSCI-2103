/**
 * Steven Ward
 * CSCI-2103
 * string_list.cpp
 */

#include <iostream>
#include <string>

#include <stddef.h>

template<class E>
class List {
    typedef E value_t;

  public:
    inline size_t size( ) const { return size_; }
    inline bool isEmpty( ) const { return !head_; }

  private:
    struct Node {
        value_t data{ };
        Node* next{nullptr};

        Node( ) = default;
        Node(value_t const& data, Node const* next = nullptr)
                : data(new value_t(data)), next(next) { }
    };

    Node* head_{nullptr};
    size_t size_{0};
};
