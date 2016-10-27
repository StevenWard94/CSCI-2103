/***********************************************************************************//**
 * Author:       Steven Ward <stevenward94@gmail.com>
 * File:         csci-2103/Structures/src/LinkStack.cpp
 * URL:          https://github.com/StevenWard94/csci-2103
 * Last Change:  2016 Oct 26
 ***********************************************************************************/

#include <string>
#include <utility>

#include <stddef.h>

template<class T>
class LinkStack {

    struct Node;
  public:
    inline T const& top( ) const { return top_->data; }
    inline size_t size( ) const { return size_; }

    inline bool isEmpty( ) const { return !top_; }
    inline constexpr bool isFull( ) const { return false; }

    LinkStack<T>& push(T const& val);
    LinkStack<T>& push(T&& val);

    LinkStack<T>& pop( );
    T&& pop_get( );

    LinkStack<T>& copy( ) const;
    LinkStack<T>& clear( );

    LinkStack<T>& operator= (LinkStack<T> const& rhs);
    LinkStack<T>& operator= (LinkStack<T>&& rhs);

    inline LinkStack( ) : top_(nullptr), size_(0) { }
    LinkStack(Node const* top);
    LinkStack(LinkStack<T> const& other);
    LinkStack(LinkStack<T>&& other);

    ~LinkStack( );

  private:
    struct Node {
        T data;
        Node* next;

        Node(T const& t = T(), Node const* node = nullptr) : data(t), next(node) { }
        Node(T&& t, Node const* node = nullptr) : data(std::forward<T>(t)), next(node) { }

        ~Node() = default;
    };
    Node* top_;
    size_t size_;

};


template<class T>
LinkStack<T>::LinkStack(Node const* top) : top_(top), size_(0) {
    Node const* it = this->top_;
    while (it != nullptr) {
        ++size_;
        it = it->next;
    }
}


template<class T>
LinkStack<T>::LinkStack(LinkStack<T> const& other) : LinkStack( ) {
    Node const* inputIt = other.top_;
    Node* outputIt = this->top_;

    while (inputIt != nullptr) {
        outputIt = new Node(inputIt->data);
        ++this->size_;
        outputIt = outputIt->next;
        inputIt = inputIt->next;
    }
}
