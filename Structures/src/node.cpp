/***************************************************************************//**
 * Author:       Steven Ward <stevenward94@gmail.com>
 * File:         <repository-root-dir>/Structures/src/node_operators.cpp
 * URL:          https://github.com/StevenWard94/csci-2103
 * Last Change:  2016 Oct 18
 ******************************************************************************/

#include "node.h"

#include <iostream>
#include <stddef.h>

template<class T>
std::ostream& operator<<(std::ostream& os, Node<T> const& node) {
    os << node.data();
    return os;
}

template<class T>
std::ostream& operator<<(std::ostream& os, Node<T> const* const node) {
    os << *node;
    return os;
}

template<class T>
std::istream& operator>>(std::istream& is, Node<T>& node) {
    Node<T>* init_next = node.next();
    T init_data = node.data();
    T data_in;
    is >> data_in;
    node.data(data_in);

    if (node.data() != data_in || node.next() != init_next) {
        node.data(init_data);
        node.next(init_next);
        is.setstate(std::ios::failbit);
    }
    return is;
}
