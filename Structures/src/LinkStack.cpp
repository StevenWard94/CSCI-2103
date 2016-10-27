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

    LinkStack<T>& push(T const& t);
    LinkStack<T>& push(T&& t);

    LinkStack<T>& pop( );
    typename std::remove_reference<T>::type&& pop_get( );

    LinkStack<T>& copy( ) const;
    LinkStack<T>& clear( );

    LinkStack<T>& operator= (LinkStack<T> const& rhs);
    LinkStack<T>& operator= (LinkStack<T>&& rhs);

    inline LinkStack( ) : top_(nullptr), size_(0) { }
    LinkStack(Node const* top);

    inline LinkStack(LinkStack<T> const& other) : top_(new Node(*(other.top_))), size_(other.size_) { }
    inline LinkStack(LinkStack<T>&& other)
            : top_(std::move(*(other.top_))), size_(std::move(other.size_)) { other.top_ = nullptr; }

    ~LinkStack( );

  private:
    struct Node {
        T data;
        Node* next;

        Node(T const& t = T(), Node const* node = nullptr) : data(t), next(node) { }
        Node(T&& t, Node const* node = nullptr) : data(std::forward<T>(t)), next(node) { }
        Node(Node const& other) : data(T(other.data)), next(new Node(*(other.next))) { }
        Node(Node&& other) : data(std::move(other.data)), next(std::move(other.next)) {
            other.next = nullptr;
        }

        Node& operator= (Node const& other) = delete;
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
LinkStack<T>& LinkStack<T>::push(T const& t) {
    Node const* const pushed = this->top_;
    this->top_ = new Node(t, pushed);
    ++this->size_;
    return *this;
}


template<class T>
LinkStack<T>& LinkStack<T>::push(T&& t) {
    Node const* const pushed = this->top_;
    this->top_ = new Node (std::forward<T>(t), pushed);
    ++this->size_;
    return *this;
}


template<class T>
LinkStack<T>& LinkStack<T>::pop( ) {
    Node const* const popped = this->top_;
    this->top_ = popped->next;
    --this->size_;
    delete popped;
    return *this;
}


template<class T>
typename std::remove_reference<T>::type&& LinkStack<T>::pop_get( ) {
    Node* const popped = this->top_;
    this->top_ = popped->next;
    T t_val = std::move(popped->data);
    --this->size_;
    delete popped;
    return std::forward<T>(t_val);
}


template<class T>
LinkStack<T>& LinkStack<T>::copy( ) const {
    return std::forward<LinkStack<T>>(*this);
}


template<class T>
LinkStack<T>& LinkStack<T>::clear( ) {
    while (!this->isEmpty()) {
        this->pop();
    }
    this->size_ = 0;
    delete this->top_;
    this->top_ = nullptr;
    return *this;
}


template<class T>
LinkStack<T>& LinkStack<T>::operator= (LinkStack<T> const& rhs) {
    if (this != &rhs) {
        delete this->top_;
        this->top_ = new Node(*(rhs.top_));
        this->size_ = rhs.size_;
    }
    return *this;
}


template<class T>
LinkStack<T>& LinkStack<T>::operator= (LinkStack<T>&& rhs) {
    return *this;
}


/*****************************************************************************
 **********  END OF LINKSTACK<T> CLASS DEFINITION & IMPLEMENTATION  **********
 *****************************************************************************/

int main(int argc, char** argv) {

    return 0;
}
