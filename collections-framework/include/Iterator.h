/***********************************************************************************//**
 * Author:       Steven Ward <stevenward94@gmail.com>
 * File:         <repository-root-dir>/collections-framework/include/Iterator.h
 * URL:          https://github.com/StevenWard94/csci-2103/tree/collections-framework
 * Last Change:  2016 Oct 20
 ***********************************************************************************/
#ifndef COLLECTIONS_FRAMEWORK_INCLUDE_ITERATOR_H_
#define COLLECTIONS_FRAMEWORK_INCLUDE_ITERATOR_H_

#include "Consumer.h"
#include "Exceptions.h"

#include <type_traits>

namespace collections {

template<class E>
class Iterator {
  public:
    virtual bool hasNext( ) = 0;
    virtual E& next( ) = 0;

    inline virtual void remove( ) {
        throw UnsupportedOperationException("Iterator::remove() : implementation undefined");
    }

    template< class D
            , typename =
                typename std::enable_if<std::is_base_of<D,E>::value || std::is_same<D,E>::value>::type
            >
    void forEachRemaining(Consumer<D>& action) {
        while (hasNext()) {
            action.accept(next());
        }
    }

};
}

#endif  // (COLLECTIONS_FRAMEWORK_INCLUDE_ITERATOR_H_)
