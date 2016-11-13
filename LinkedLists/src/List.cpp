/***********************************************************************************//**
 * Author:       Steven Ward <stevenward94@gmail.com>
 * File:         csci-2103/LinkedLists/src/List.cpp
 * URL:          https://github.com/StevenWard94/csci-2103
 * Last Change:  2016 Oct 12
 ***********************************************************************************/

#include <iostream>
#include <string>
#include <type_traits>
#include <utility>

#include <stddef.h>

template<class T>
class List {
    using value_t = T;
    template<class U>
    using remove_ref = typename std::remove_reference<U>::type;
    struct Node;

  public:
    static const size_t NPOS = -1;

    inline Node const* const head( ) const { return this->head_; }
    inline size_t size( ) const { return this->size_; }
    inline remove_ref<value_t> const& front( ) const { return this->head_->data; }
    inline bool isEmpty( ) const { return this->head_ == nullptr; }

    List<value_t>& insert(value_t const& val, size_t index);
    inline List<value_t>& append(value_t const& val) { return insert(val, this->size_ - 1); }
    inline List<value_t>& prepend(value_t const& val) { return insert(val, 0); }

    size_t find(value_t const& val, size_t pos = 0) const;
    inline bool contains(value_t const& val) const { return find(val, 0) != List::NPOS; }

    value_t& at(size_t index);
    value_t& operator[](size_t index);
    value_t const& at(size_t index) const;
    value_t const& operator[](size_t index) const;

    List<value_t>& remove(value_t const& val, size_t pos = 0);
    List<value_t>& removeAt(size_t index);

    List<value_t>& clear( );
    List<value_t>& clone( ) const;

    List<value_t>& operator=(List<value_t> const& rhs);

    List( ) = default;
    List(List<value_t> const& other);

    virtual ~List( ) { clear(); }

  private:
    Node* head_{nullptr};
    size_t size_{ };

    struct Node {
        value_t data{ };
        Node* next{nullptr};

        Node( ) = default;

        Node(value_t const& val) : data{val} { }
        Node(value_t&& val) : data{std::forward<value_t>(val)} { }

        Node(Node const& other) = default;
        Node(Node&& other) = default;

        Node& operator= (Node const& rhs) = default;
        Node& operator= (Node&& rhs) = default;
    };
};


template<class T>
auto List<T>::insert(value_t const& val, size_t index) -> List<value_t>& {
    if (index < this->size_) {
        decltype(head_) nodeIt_leading = this->head_;
        decltype(head_) nodeIt_trailing = nullptr;
        for (size_t i = 0; i < index; i++) {
            nodeIt_trailing = nodeIt_leading;
            nodeIt_leading = nodeIt_leading->next;
        }
        Node* node_inserted = new Node(val);
        node_inserted->next = nodeIt_leading;
        nodeIt_trailing->next = node_inserted;
        this->size_++;
    }
    return *this;
}


template<class T>
size_t List<T>::find(value_t const& val, size_t pos/*= 0*/) const {

    size_t match_index = List<T>::NPOS;
    if (pos < this->size_) {
        decltype(head_) nodeIt = this->head_;

        for (size_t i = 0; i < pos; i++) {
            nodeIt = nodeIt->next;
        }
        size_t current_index = pos;
        while ( !(nodeIt == nullptr || match_index == List<T>::NPOS) ) {
            match_index = nodeIt->data == val ? current_index : match_index;
            nodeIt = nodeIt->next;
            current_index++;
        }
    }
    return match_index;
}
template<class T>
auto List<T>::at(size_t index) -> value_t& {
    if (index < this->size_) {
        decltype(head_) nodeIt = this->head_;
        for (size_t i = 0; i < index; i++) {
            nodeIt = nodeIt->next;
        }
        return nodeIt->data;
    }
    else {
        throw std::out_of_range("List::at(size_t index) - argument 'index' out of range : ->{List<T>}.at(" + std::to_string(index) + ")");
    }
}


template<class T>
auto List<T>::operator[](size_t index) -> value_t& {
    decltype(head_) nodeIt = this->head_;
    for (size_t i = 0; i < index; i++) {
        nodeIt = nodeIt->next;
    }
    return nodeIt->data;
}


template<class T>
const auto List<T>::at(size_t index) const -> value_t const& {
    if (index < this->size_) {
        decltype(head_) const_nodeIt = this->head_;
        for (size_t i = 0; i < index; i++) {
            const_nodeIt = const_nodeIt->next;
        }
        return const_nodeIt->data;
    }
    else {
        throw std::out_of_range("const List::at(size_t index) - argument 'index' out of range : ->{const List<T>}.at(" + std::to_string(index) + ")");
    }
}


template<class T>
const auto List<T>::operator[](size_t index) const -> value_t const& {
    decltype(head_) const_nodeIt = this->head_;
    for (size_t i = 0; i < index; i++) {
        const_nodeIt = const_nodeIt->next;
    }
    return const_nodeIt->data;
}


