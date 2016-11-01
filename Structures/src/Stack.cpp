/***********************************************************************************//**
 * Author:       Steven Ward <stevenward94@gmail.com>
 * File:         csci-2103/Structures/src/Stack.cpp
 * Last Change:  2016 Oct 26
 ***********************************************************************************/

#include <iomanip>
#include <iostream>
#include <string>
#include <utility>

#include <stddef.h>

template<class T>
class Stack {
    struct Node;

  public:
    inline T&& top( ) const { return std::forward<T>(this->top_->data); }
    inline size_t size( ) const { return this->size_; }

    inline bool isEmpty( ) const { return static_cast<bool>(this->top_); }
    inline bool isFull( ) const { return false; }

    void push(T const& item);

    void pop( );
    T&& pop_get( );

    void clear( );
    Stack<T>& clone( ) const;

    Stack<T>& operator= (Stack<T> const& rhs);

    inline Stack( ) : top_(nullptr), size_(0) { }
    inline Stack(Node* top, size_t size) : top_(new Node(*top)), size_(size) { }
    inline Stack(Stack<T> const& other)
            : top_(new Node(*other.top_)), size_(other.size_) { }

    ~Stack( );

  private:
    Node* top_;
    size_t size_;

    struct Node {
        T data;
        Node* next;

        Node( ) : data{ T() }, next(nullptr) { }
        Node(T const& item) : data(item), next(nullptr) { }
        Node(T const& item, Node const* node)
                : data(item), next(node) { }
        Node(Node const& other) : data(other.data), next(new Node(*other.next)) { }

        ~Node( ) { }
    };
};


template<class T>
void Stack<T>::push(T const& item) {
    Node const* const pushed = this->top_;
    Node const* const newNode = new Node(item, pushed);
    this->top_ = newNode;
    this->size_++;
}


template<class T>
void Stack<T>::pop( ) {
    Node const* popped = this->top_;
    this->top_ = popped->next;
    this->size_--;
    delete popped;
}


template<class T>
T&& Stack<T>::pop_get( ) {
    T popped_data = this->top();
    this->pop();
    return std::forward<T>(popped_data);
}


template<class T>
void Stack<T>::clear( ) {
    while (!this->isEmpty()) {
        this->pop();
    }
    delete this->top_;
    this->top_ = nullptr;
    this->size_ = 0;
}


template<class T>
Stack<T>& Stack<T>::clone( ) const {
    if (this->isEmpty()) {
        return *(new Stack<T>);
    }
    else {
        Node* clone_top = new Node(*this->top_);
        Node* inputIt = clone_top->next;
        Node const* outputIt = this->top_->next;

        while (outputIt != nullptr) {
            inputIt = new Node(*outputIt);
            outputIt = outputIt->next;
            inputIt = inputIt->next;
        }
        return *(new Stack<T>(clone_top, this->size_));
    }
}


template<class T>
Stack<T>& Stack<T>::operator= (Stack<T> const& rhs) {
    if (this != &rhs) {
        delete this->top_;
        this->size_ = rhs.size_;
        this->top_ = std::move(rhs.clone().top_);
    }
    return *this;
}


template<class T>
Stack<T>::~Stack( ) {
    this->clear( );
}


int main(int argc, char** argv) {
    std::string strArray[10];
    std::cout << "instantiated 'strArray'\n";

    for (size_t i = 0; i < 10; i++) {
        strArray[i] = "This is a string.";
        std::cout << "added 'strArray[" << i << "]'\n";
    }

    Stack<std::string> strPile;
    std::cout << "default constructed 'strPile'\n";
    for (size_t i = 0; i < 10; i++) {
        strPile.push(strArray[i]);
        std::cout << "pushed 'strArray[" << i << "]' onto 'strPile'\n";
    }

    Stack<std::string> copy1(strPile);
    std::cout << "copy-constructed 'copy1'\n";
    Stack<std::string> copy2;
    copy2 = strPile;
    std::cout << "assigned 'strPile' to 'copy2'\n";

    std::cout << std::left << std::setw(20) << "STR_PILE"
            << std::setw(20) << "COPY_ONE" << std::setw(20) << "COPY_TWO" << std::endl;

    while (!(strPile.isEmpty() || copy1.isEmpty() || copy2.isEmpty())) {
        std::cout << std::left;
        std::cout << std::setw(20) << strPile.pop_get() << std::setw(20)
                << copy1.pop_get() << std::setw(20) << copy2.pop_get() << std::endl
                << std::setw(20) << strPile.size() << std::setw(20) << copy1.size()
                << std::setw(20) << copy2.size() << std::endl;
    }
    std::cin.ignore();
    return 0;
}
