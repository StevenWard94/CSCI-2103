/***************************************************************************//**
 * Author:       Steven Ward <stevenward94@gmail.com>
 * File:         <repository-root-dir>/Structures/include/ArrayList.h
 * URL:          https://github.com/StevenWard94/csci-2103
 * Last Change:  2016 Oct 19
 *
 * Implementation of a fixed-size list built on an array.
 ****************************************************************************/

#ifndef STRUCTURES_INCLUDE_FIXED_SIZE_ARRAY_LIST_H_
#define STRUCTURES_INCLUDE_FIXED_SIZE_ARRAY_LIST_H_

#include "node.h"

#include <iterator>
#include <stddef.h>

namespace fixed_size {

template<class T, size_t SIZE>
class ArrayList {
  using node_type = Node<T>;

  using value_type = T;
  using reference = T&;
  using pointer = T*;

  public:
    static const size_t NPOS = -1;

    class iterator : public std::iterator<std::forward_iterator_tag, T>
    {
        node_type* rep_;
      public:
        friend class const_iterator;

        inline iterator(node_type* node = nullptr) : rep_(node) { }
        inline iterator(iterator const& it) : rep_(it.rep_) { }

        inline iterator& operator= (iterator const& rhs) {
            this->rep_ = rhs.rep_;
            return *this;
        }

        // so far, this can only be a forward_iterator - need to extend Node<T>
        // to define a doubly-linked node for reverse_iterator functionality

        inline iterator operator++(int) {
            iterator init(*this);
            this->rep_ = rep_->next();
            return init;
        }

        inline iterator& operator++( ) {
            this->rep_ = rep_->next();
            return *this;
        }

        inline reference operator* ( ) const { return rep_->data(); }
        inline pointer operator->( ) const { return rep_; }
        inline bool operator==(iterator const& rhs) const {
            return this->rep_ == rhs.rep_;
        }
        inline bool operator!=(iterator const& rhs) const {
            return !this->operator==(rhs);
        }
    };

    class const_iterator : public std::iterator<std::forward_iterator_tag, T const>
    {
        node_type const* rep_;
      public:
        friend class iterator;

        inline const_iterator(node_type const* node = nullptr) : rep_(node) { }
        inline const_iterator(const_iterator const& it) : rep_(it.rep_) { }
        inline const_iterator(iterator const& it) : rep_(it.rep_) { }

        inline const_iterator& operator= (const_iterator const& rhs) {
            this->rep_ = rhs.rep_;
            return *this;
        }

        inline const_iterator& operator++(int) {
            const_iterator init(*this);
            this->rep_ = rep_->next();
            return init;
        }

        inline const_iterator& operator++( ) {
            this->rep_ = rep_->next();
            return *this;
        }

        inline reference operator* ( ) const { return this->rep_->data(); }
        inline pointer operator->( ) const { return this->rep_; }
        inline bool operator==(const_iterator const& rhs) const {
            return this->rep_ == rhs.rep_;
        }
        inline bool operator!=(const_iterator const& rhs) const {
            return !this->operator==(rhs);
        }
    };

    inline ArrayList( ) : length_(0), begin_(nullptr), end_(node_type()) { }
    ArrayList(value_type const& );
    template <class InputIterator>
      ArrayList(InputIterator , InputIterator );
    ArrayList(ArrayList<value_type, SIZE> const& );

    inline bool isEmpty( ) const { return begin_ == nullptr; }
    inline bool isFull( ) const { return length_ == SIZE_; }

    inline size_t length( ) const { return length_; }
    inline size_t capacity( ) const { return SIZE_; }
    inline size_t open( ) const { return SIZE_ - length_; }

    inline iterator& begin( ) { return iterator(begin_); }
    inline const_iterator& begin( ) const { return const_iterator(begin_); }
    inline iterator& end( ) { return iterator(end_); }
    inline const_iterator& end( ) const { return const_iterator(end_); }

    bool contains(value_type const& ) const;
    value_type& at(size_t );
    value_type const& at(size_t ) const;
    value_type& operator[](size_t );
    value_type const& operator[](size_t ) const;

    size_t find(value_type const& , size_t pos = 0) const;
    size_t* findN(size_t , value_type const& , size_t pos = 0) const;

    ArrayList<value_type, SIZE>& push_front(value_type const& );
    ArrayList<value_type, SIZE>& push_back(value_type const& );
    ArrayList<value_type, SIZE>& pop_front( );
    ArrayList<value_type, SIZE>& pop_back( );
    ArrayList<value_type, SIZE>& insert(size_t );
    ArrayList<value_type, SIZE>& insertAfter(value_type const& );
    ArrayList<value_type, SIZE>& insertAfter(iterator );
    ArrayList<value_type, SIZE>& insertBefore(value_type const& );

  private:
    const size_t SIZE_ = SIZE;
    size_t length_;
    iterator begin_;
    iterator end_;
};
}

#endif  // (STRUCTURES_INCLUDE_FIXED_SIZE_ARRAY_LIST_H_)
