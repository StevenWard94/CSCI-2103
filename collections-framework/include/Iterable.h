/***********************************************************************************//**
 * Author:       Steven Ward <stevenward94@gmail.com>
 * File:         <repository-root-dir>/collections-framework/include/Iterable.h
 * URL:          https://github.com/StevenWard94/csci-2103/tree/collections-framework
 * Last Change:  2016 Oct 21
 ***********************************************************************************/
#ifndef COLLECTIONS_FRAMEWORK_INCLUDE_ITERABLE_H_
#define COLLECTIONS_FRAMEWORK_INCLUDE_ITERABLE_H_

#include "Consumer.h"
#include "Iterator.h"
#include "Spliterator.h"  // just declares undefined 'Spliterator' class, as of last edit

#include "util_lib.h"

#include <type_traits>


template<class T>
class Iterable {
  public:
    virtual collections::Iterator<T> iterator( ) = 0;

    template<class S, typename = util_lib::super<T,S>>
    void forEach(Consumer<S> action) {
        for (T& t : this) {
            action.accept(t);
        }
    }

  #ifdef SPLITERATOR
    virtual collections::Spliterator<T> spliterator( ) {
        return Spliterators.spliteratorUnknownSize(iterator(), 0);
    }
  #endif

};


#endif  // (COLLECTIONS_FRAMEWORK_INCLUDE_ITERABLE_H_)
