/***********************************************************************************//**
 * Author:       Steven Ward <stevenward94@gmail.com>
 * File:         <repository-root-dir>/collections-framework/include/Collection.h
 * URL:          https://github.com/StevenWard94/csci-2103/tree/collections-framework
 * Last Change:  2016 Oct 21
 ***********************************************************************************/
#ifndef COLLECTIONS_FRAMEWORK_INCLUDE_COLLECTION_H_
#define COLLECTIONS_FRAMEWORK_INCLUDE_COLLECTION_H_

#include "Consumer.h"
#include "Iterable.h"
#include "Iterator.h"

#include "util_lib.h"

#include <cstdint>
#include <type_traits>

namespace collections {

template<class E>
class Collection : public Iterable<E> {
  public:
    virtual std::int32_t size( ) const = 0;

    virtual bool isEmpty( ) const = 0;

    virtual bool contains(E& e) const = 0;

    virtual collections::Iterator<E> iterator( ) const = 0;

    virtual E* toArray( ) const = 0;

    virtual E* toArray(E a[]) const = 0;

    virtual bool add(E e) = 0;

    virtual bool remove(E e) = 0;

    template<class F, typename = util_lib::extends<E,F>>
    bool addAll(Collection<F>& c);

    template<class T>
    bool removeAll(Collection<T>& c);
};
}

#endif  // (COLLECTIONS_FRAMEWORK_INCLUDE_COLLECTION_H_)
