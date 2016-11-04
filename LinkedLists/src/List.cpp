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
    static const size_t NPOS = -1;

    inline Node const* head( ) const { return this->head_; }
    inline Node const* tail( ) const { return this->tail_; }
    inline size_t size( ) const { return this->size_; }

    inline value_t front( ) const { return std::forward<Node*>(head_)->data; }
    inline value_t back( ) const { return std::forward<Node*>(tail_)->data; }
    inline bool isEmpty( ) const { return head_ == nullptr; }

    List<value_t>& append(value_t const& val);
    List<value_t>& append(value_t&& val);
    List<value_t>& prepend(value_t const& val);
    List<value_t>& prepend(value_t&& val);
    List<value_t>& insert(value_t const& val, size_t pos);
    List<value_t>& insert(value_t&& val, size_t pos);

    size_t find(value_t const& val, size_t pos = 0) const;
    size_t find(value_t&& val, size_t pos = 0) const;

    value_t& at(size_t index);
    value_t const& at(size_t index) const;
    value_t& operator[](size_t index);
    value_t const& operator[](size_t index) const;

    List<value_t>& remove(value_t const& val, size_t pos = 0);
    List<value_t>& remove(value_t&& val, size_t pos = 0);
    List<value_t>& removeAt(size_t index);

    List<value_t>& clear( );
    List<value_t>& clone( );

    List<value_t>& operator= (List<value_t> const& rhs);
    List<value_t>& operator= (List<value_t>&& rhs);

    List( ) = default;
    List(List<value_t> const& other);
    List(List<value_t>&& other);

    virtual ~List( );

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

        Node(value_t const& val, Node* node) : Node(val) { this->next = node; }
        Node(value_t&& val, Node* node)
                : Node(std::forward<value_t>(val)) { this->next = node; }

        Node(Node const& other)
                : data{ new value_t(other.data) }, next{ new Node(*other.next) } { }

        Node(Node&& other)
                : data{ std::move(other.data) }, next{ std::move(other.next) }
        { other.next = nullptr; }
    };
    List<value_t>& add_isEmpty(value_t const& val);
    List<value_t>& add_isEmpty(value_t&& val);

};  // End definition of List class template


// Begin implementation of List class template
template<typename T>
inline List<T>& List<T>::add_isEmpty(typename List<T>::value_t const& val) {
    Node* const node_add = new Node(val);
    this->head_ = node_add;
    this->tail_ = node_add;
    this->size_++;
    return *this;
}


template<typename T>
inline List<T>& List<T>::add_isEmpty(typename List<T>::value_t&& val) {
    Node* const node_add = new Node(std::forward<value_t>(val));
    this->head_ = node_add;
    this->tail_ = node_add;
    this->size_++;
    return *this;
}


template<typename T>
inline List<T>& List<T>::append(typename List<T>::value_t const& val) {
    if (!this->isEmpty()) {
        Node* const node_append = new Node(val);
        this->tail_->next = node_append;
        this->tail_ = node_append;
        this->size_++;
        return *this;
    }
    else {
        return add_isEmpty(val);
    }
}


template<typename T>
inline List<T>& List<T>::append(typename List<T>::value_t&& val) {
    if (!this->isEmpty()) {
        Node* const node_append = new Node(std::forward<value_t>(val));
        this->tail_->next = node_append;
        this->tail_ = node_append;
        this->size_++;
        return *this;
    }
    else {
        return add_isEmpty(std::forward<value_t>(val));
    }
}


template<typename T>
inline List<T>& List<T>::prepend(typename List<T>::value_t const& val) {
    if (!this->isEmpty()) {
        Node* const node_prepend = new Node(val, this->head_);
        this->head_ = node_prepend;
        this->size_++;
        return *this;
    }
    else {
        return add_isEmpty(val);
    }
}


template<typename T>
inline List<T>& List<T>::prepend(typename List<T>::value_t&& val) {
    if (!this->isEmpty()) {
        Node* const node_prepend = new Node(std::forward<value_t>(val), this->head_);
        this->head_ = node_prepend;
        this->size_++;
        return *this;
    }
    else {
        return add_isEmpty(std::forward<value_t>(val));
    }
}


template<typename T>
inline List<T>& List<T>::insert(typename List<T>::value_t const& val, size_t pos) {
    if (pos < this->size_ - 1 && pos > 0) {
        Node* nodeIt = this->head_;
        for (size_t i = 0; i < pos - 1; i++) {
            nodeIt = nodeIt->next;
        }  // nodeIt now points to the node directly before the insertion point
        Node* const node_next = nodeIt->next;
        nodeIt->next = new Node(val, node_next);
        this->size_++;
        return *this;
    }
    else if (pos == this->size_ - 1) {
        return append(val);
    }
    else if (pos == 0) {
        return prepend(val);
    }
    else if (pos >= this->size_) {
        throw std::out_of_range("List<T>::insert(const T&, size_t) : arg 'size_t pos', value " + std::to_string(pos) + " - out of range");
    }
    else {
        throw std::domain_error("List<T>::insert(const T&, size_t) : arg 'size_t pos', unexpected value, " + std::to_string(pos));
    }
}


template<typename T>
inline List<T>& List<T>::insert(typename List<T>::value_t&& val, size_t pos) {
    using value_t = typename List<T>::value_t;
    if (pos < this->size_ - 1 && pos > 0) {
        Node* nodeIt = this->head_;
        for (size_t i = 0; i < pos - 1; i++) {
            nodeIt = nodeIt->next;
        }  // nodeIt now points to the node directly before the insertion point
        Node* const node_next = nodeIt->next;
        nodeIt->next = new Node(std::forward<value_t>(val), node_next);
        this->size_++;
        return *this;
    }
    else if (pos == this->size_ - 1) {
        return append(std::forward<value_t>(val));
    }
    else if (pos == 0) {
        return prepend(std::forward<value_t>(val));
    }
    else if (pos >= this->size_) {
        throw std::out_of_range("List<T>::insert(T&&, size_t) : arg 'size_t pos', value " + std::to_string(pos) + " - out of range");
    }
    else {
        throw std::domain_error("List<T>::insert(T&&, size_t) : arg 'size_t pos', unexpected value, " + std::to_string(pos));
    }
}


template<typename T>
inline size_t List<T>::find(typename List<T>::value_t const& val, size_t pos/*= 0*/) const {
    if (pos < this->size_) {
        Node const* nodeIt = this->head_;
        for (size_t i = 0; i < pos; i++) {
            nodeIt = nodeIt->next;
        } // nodeIt now points to the node in position 'pos'
        size_t index = pos;
        while (nodeIt != this->tail_->next) {
            if (nodeIt->data == val) {
                return index;
            }
            else {
                nodeIt = nodeIt->next;
                index++;
            }
        }
        return List::NPOS;
    }
    else if (pos >= this->size_) {
        throw std::out_of_range("List<T>::find(const T&, size_t) : arg 'size_t pos', value " + std::to_string(pos) + " - out of range");
    }
    else {
        throw std::domain_error("List<T>::find(const T&, size_t) : arg 'size_t pos', unexpected value, " + std::to_string(pos));
    }
}


template<typename T>
inline size_t List<T>::find(typename List<T>::value_t&& val, size_t pos/*= 0*/) const {
    if (pos < this->size_) {
        Node const* nodeIt = this->head_;
        for (size_t i = 0; i < pos; i++) {
            nodeIt = nodeIt->next;
        } // nodeIt now points to the node in position 'pos'
        size_t index = pos;
        while (nodeIt != this->tail_->next) {
            if (nodeIt->data == val) {
                return index;
            }
            else {
                nodeIt = nodeIt->next;
                index++;
            }
        }
        return List::NPOS;
    }
    else if (pos >= this->size_) {
        throw std::out_of_range("List<T>::find(T&&, size_t) : arg 'size_t pos', value " + std::to_string(pos) + " - out of range");
    }
    else {
        throw std::domain_error("List<T>::find(T&&, size_t) : arg 'size_t pos', unexpected value, " + std::to_string(pos));
    }
}


template<typename T>
inline typename List<T>::value_t& List<T>::at(size_t index) {
    if (index < this->size_) {
        Node* nodeIt = this->head_;
        for (size_t i = 0; i < index; i++) {
            nodeIt = nodeIt->next;
        }
        return nodeIt->data;
    }
    else if (index >= this->size_) {
        throw std::out_of_range("List<T>::at(size_t) : arg 'size_t index', value " + std::to_string(index) + " - out of range");
    }
    else {
        throw std::domain_error("List<T>::at(size_t) : arg 'size_t index', unexpected value, " + std::to_string(index));
    }
}


template<typename T>
inline typename List<T>::value_t& List<T>::operator[](size_t index) {
    Node* nodeIt = this->head_;
    for (size_t i = 0; i < index; i++) {
        nodeIt = nodeIt->next;
    }
    return nodeIt->data;
}


template<typename T>
inline typename List<T>::value_t const& List<T>::at(size_t index) const {
    if (index < this->size_) {
        Node const* const_nodeIt = this->head_;
        for (size_t i = 0; i < index; i++) {
            const_nodeIt = const_nodeIt->next;
        }
        return const_nodeIt->data;
    }
    else if (index >= this->size_) {
        throw std::out_of_range("const List<T>::at(size_t) : arg 'size_t index', value " + std::to_string(index) + " - out of range");
    }
    else {
        throw std::domain_error("const List<T>::at(size_t) : arg 'size_t index', unexpected value, " + std::to_string(index));
    }
}


template<typename T>
inline typename List<T>::value_t const& List<T>::operator[](size_t index) const {
    Node const* const_nodeIt = this->head_;
    for (size_t i = 0; i < index; i++) {
        const_nodeIt = const_nodeIt->next;
    }
    return const_nodeIt->data;
}


template<typename T>
inline List<T>& List<T>::remove(typename List<T>::value_t const& val, size_t pos/*= 0*/) {
    if (pos < this->size_) {
        size_t rm_index = find(val, pos);

        if (rm_index != List::NPOS) {
            Node* nodeIt_lead = this->head_;
            Node* nodeIt_trail = nullptr;

            for (size_t i = 0; i < rm_index; i++) {
                nodeIt_trail = nodeIt_lead;
                nodeIt_lead = nodeIt_trail->next;
            } // nodeIt_lead now points at the node that is to be removed

            Node* const node_after = nodeIt_lead->next;
            nodeIt_trail->next = node_after;
            delete nodeIt_trail;
            this->size_--;
        }
        return *this;
    }
    else if (pos >= this->size_) {
        throw std::out_of_range("List<T>::remove(const T&, size_t) : arg 'size_t pos', value " + std::to_string(pos) + " - out of range");
    }
    else {
        throw std::domain_error("List<T>::remove(const T&, size_t) : arg 'size_t pos', unexpected value, " + std::to_string(pos));
    }
}


template<typename T>
inline List<T>& List<T>::remove(typename List<T>::value_t&& val, size_t pos/*= 0*/) {
    if (pos < this->size_) {
        size_t rm_index = find(std::forward<value_t>(val), pos);

        if (rm_index != List::NPOS) {
            Node* nodeIt_lead = this->head_;
            Node* nodeIt_trail = nullptr;

            for (size_t i = 0; i < rm_index; i++) {
                nodeIt_trail = nodeIt_lead;
                nodeIt_lead = nodeIt_trail->next;
            } // nodeIt_lead now points at the node that is to be removed

            Node* const node_after = nodeIt_lead->next;
            nodeIt_trail->next = node_after;
            delete nodeIt_trail;
            this->size_--;
        }
        return *this;
    }
    else if (pos >= this->size_) {
        throw std::out_of_range("List<T>::remove(T&&, size_t) : arg 'size_t pos', value " + std::to_string(pos) + " - out of range");
    }
    else {
        throw std::domain_error("List<T>::remove(T&&, size_t) : arg 'size_t pos', unexpected value, " + std::to_string(pos));
    }
}


template<typename T>
inline List<T>& List<T>::removeAt(size_t index) {
    if (index < this->size_) {
        Node* nodeIt_lead = this->head_;
        Node* nodeIt_trail = nullptr;
        for (size_t i = 0; i < index; i++) {
            nodeIt_trail = nodeIt_lead;
            nodeIt_lead = nodeIt_trail->next;
        }
        Node* const node_after = nodeIt_lead->next;
        nodeIt_trail->next = node_after;
        delete nodeIt_lead;
        this->size_--;
    }
    return *this;
}


template<typename T>
inline List<T>& List<T>::clear( ) {
    Node* garbage_collector = this->head_;
    while (garbage_collector != this->tail_->next) {
        Node* tmp = garbage_collector;
        garbage_collector = tmp->next;
        delete tmp;
        this->size_--;
    }
    delete this->head_;
    this->head_ = nullptr;
    delete this->tail_;
    this->tail_ = nullptr;
    return *this;
}


template<typename T>
inline List<T>& List<T>::operator= (List<value_t> const& rhs) {
    if (this != &rhs) {
        this->clear();
        Node const* inputIt = rhs.head_;
        Node* outputIt = this->head_;

        while (inputIt != nullptr) {
            outputIt = new Node(inputIt->data);
            this->size_++;
            inputIt = inputIt->next;
            outputIt = inputIt != nullptr ? outputIt->next : outputIt;
        }
        this->tail_ = outputIt;
    }
    return *this;
}


template<typename T>
inline List<T>& List<T>::operator= (List<value_t>&& rhs) {
    if (this != &rhs) {
        this->clear();
        Node* inputIt = std::forward<List<value_t>>(rhs).head_;
        Node* outputIt = this->head_;

        while (inputIt != nullptr) {
            outputIt = new Node(std::forward<Node>(*inputIt).data);
            this->size_++;
            inputIt = std::forward<Node>(*inputIt).next;
            outputIt = outputIt->next;
        }
        this->tail_ = outputIt;
    }
    return *this;
}


template<typename T>
inline List<T>::List(List<value_t> const& other) : List() {
    this->size_ = other.size_;
    Node const* inputIt = other.head_;
    Node* outputIt = this->head_;

    while (inputIt != nullptr) {
        outputIt = new Node(inputIt->data);
        inputIt = inputIt->next;
        outputIt = outputIt->next;
    }
    this->tail_ = outputIt;
}


template<typename T>
inline List<T>::List(List<value_t>&& other) {
    this->size_ = other.size_;
    Node* inputIt = std::forward<List<value_t>>(other).head_;
    Node* outputIt = this->head_;

    while (inputIt != nullptr) {
        outputIt = new Node(std::forward<Node>(*inputIt).data);
        inputIt = std::forward<Node>(*inputIt).next;
        outputIt = outputIt->next;
    }
    this->tail_ = outputIt;
}
