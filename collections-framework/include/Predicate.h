/***********************************************************************************//**
 * Author:       Steven Ward <stevenward94@gmail.com>
 * File:         <repository-root-dir>/collections-framework/include/Predicate.h
 * URL:          https://github.com/StevenWard94/csci-2103/tree/collections-framework
 * Last Change:  2016 Oct 21
 ***********************************************************************************/
#ifndef COLLECTIONS_FRAMEWORK_INCLUDE_PREDICATE_H_
#define COLLECTIONS_FRAMEWORK_INCLUDE_PREDICATE_H_

#include "util_lib.h"

#include <stddef.h>

template<class T>
class Predicate {
  public:
    virtual bool test(T const& t) const = 0;

    template<class U, typename = util_lib::super<T,U>>
    Predicate<T>& and_(Predicate<U> const& other) const {
        return [&](T t) { test(t) && other.test(t); };
    }

    virtual Predicate<T>& negate( ) const {
        return [this](T t) { !test(t); };
    }

    template<class U, typename = util_lib::super<T,U>>
    Predicate<T>& or_(Predicate<U> const& other) const {
        return [&](T t) { test(t) || other.test(t); };
    }

    template<class Object>
    static Predicate<T>& isEqual(Object targetRef) {
        return (targetRef == nullptr)
                ? util_lib::isNull
                : [&](Object object) { targetRef.equals(object); };
    }

};

#endif  // (COLLECTIONS_FRAMEWORK_INCLUDE_PREDICATE_H_)
