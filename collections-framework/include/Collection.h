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
#include "Predicate.h"

#include "util_lib.h"

#include <iostream>

namespace collections {

template<class E>
class Collection : public Iterable<E> {
  public:
    virtual std::int32_t size( ) const = 0;

    virtual bool isEmpty( ) const = 0;

    virtual bool contains(E const& e) const = 0;

    virtual collections::Iterator<E>& iterator( ) const = 0;

    virtual E* toArray( ) const = 0;

    template<class D, typename = util_lib::super<E,D>>
    D* toArray(D* const a) const;

    virtual bool add(E const& e) = 0;

    template<class T, typename = util_lib::related<E,T>>
    bool remove(T t);

    template<class T, typename = util_lib::related<E,T>>
    bool containsAll(Collection<T> const& c) const;

    template<class F, typename = util_lib::extends<E,F>>
    bool addAll(Collection<F> const& c);

    template<class T, typename = util_lib::related<E,T>>
    bool removeAll(Collection<T> const& c);

    template<class D, typename = util_lib::super<E,D>>
    bool removeIf(Predicate<D> const& filter) {
        bool removed = false;
        const Iterator<E> each = iterator();
        while (each.hasNext()) {
            if (filter.test(each.next())) {
                each.remove();
                removed = true;
            }
        }
        return removed;
    }

    template<class T, typename = util_lib::related<E,T>>
    bool retainAll(Collection<T> const& c);

    virtual void clear( ) = 0;

    template<class Object>
    bool equals(Object const& o) const;

    std::int32_t hashCode( ) const = 0;


};
}

#endif  // (COLLECTIONS_FRAMEWORK_INCLUDE_COLLECTION_H_)
