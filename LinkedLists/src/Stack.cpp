/***********************************************************************************//**
 * Author:       Steven Ward <stevenward94@gmail.com>
 * File:         csci-2103/LinkedLists/src/Stack.cpp
 * URL:          https://github.com/StevenWard94/csci-2103
 * Last Change:  2016 Oct 26
 ***********************************************************************************/

#include <iomanip>
#include <iostream>
#include <stdexcept>
#include <string>
#include <utility>

#include <stdlib.h>

template<typename T>
class Stack {
    using value_t = T;
    struct Node;

  public:
    inline value_t&& top( ) const {
        if (!this->isEmpty()) {
            return std::forward<value_t>(top_->data);
        }
        else {
            throw std::domain_error("Stack<T>::top() : cannot return top of empty stack");
        }
    }


    inline size_t size( ) const { return size_; }
    inline bool isEmpty( ) const { return static_cast<bool>(top_); }
    inline bool isFull( ) const { return false; }

    inline Stack<T>& push(T const& item) {

    }
};
