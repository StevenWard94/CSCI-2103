/***********************************************************************************//**
 * Author:       Steven Ward <stevenward94@gmail.com>
 * File:         csci-2103/Structures/include/basic_node.h
 * URL:          https://github.com/StevenWard94/csci-2103
 * Last Change:  2016 Oct 26
 ***********************************************************************************/

#ifndef STRUCTURES_INCLUDE_BASE_BASIC_NODE_H_
#define STRUCTURES_INCLUDE_BASE_BASIC_NODE_H_

#include <utility>

namespace base {

template<class E>
struct basic_node {
    using value_t = E;

    value_t data;
    basic_node* next;

    inline value_t const& copy_data( ) const { return value_t(this->data); }

    inline basic_node(value_t const& val = value_t(), basic_node const* nxt = nullptr)
            : data(val), next(nxt) { }

    /* copy semantics */
    inline basic_node(basic_node const& other) : data(other.data), next(other.next) { }
    inline basic_node(basic_node const* other) : basic_node(*other) { }

    inline basic_node& operator=(basic_node const& other) {
        if (this != &other) {
            data = other.data;
            delete next;
            next = other.next;
        }
        return *this;
    }
    inline basic_node& operator=(basic_node const* other) { return this->operator=(*other); }

    /* move semantics */
    inline basic_node(basic_node&& other) : data(std::move(other.data)), next(other.next) {
        other.data = value_t();
        other.next = nullptr;
    }

    inline basic_node& operator=(basic_node&& other) {
        swap(*this, other);
        return *this;
    }



    friend void swap(basic_node& lhs, basic_node& rhs) {
        basic_node tmp(std::move(lhs));
        lhs = std::move(rhs);
        rhs = std::move(tmp);
    }
};

} /* end namespace base */

#endif  // (STRUCTURES_INCLUDE_BASE_BASIC_NODE_H_)
