/***********************************************************************************//**
 * Author:       Steven Ward <stevenward94@gmail.com>
 * File:         csci-2103/Structures/src/Stack.cpp
 * Last Change:  2016 Oct 26
 ***********************************************************************************/

#include <iostream>
#include <string>
#include <utility>

#include <stddef.h>

template<class T>
class Stack {
    struct Node;

  public:
    inline T& top( ) const { return this->top_; }
    inline size_t size( ) const { return this->size_; }

    inline bool isEmpty( ) const { return static_cast<bool>(this->top_); }
    inline bool isFull( ) const { return false; }

    void push(T const& item);

    void pop( );
    T& pop_get( );

    void clear( );
    Stack<T>& clone( ) const;

    Stack<T>& operator= (Stack<T> const& rhs);

    inline Stack( ) : top_(nullptr), size_(0) { }
    inline Stack(Stack<T> const& other)
            : top_(new Node(*other.top_)), size_(other.size_) { }

    ~Stack( );

  private:
    Node* top_;
    size_t size_;

    struct Node {
        T data{ T() };
        Node* next{ nullptr };

        Node( ) = default;
        Node(T const& item) : data(item) { }
        Node(T const& item, Node* node) : data(item), next(node) { }
        Node(Node const& other) : data(other.data), next(other.next) { }

        ~Node( ) = default;
    };
};

