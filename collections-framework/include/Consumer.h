/***********************************************************************************//**
 * Author:       Steven Ward <stevenward94@gmail.com>
 * File:         <repository-root-dir>/collections-framework/include/Consumer.h
 * URL:          https://github.com/StevenWard94/csci-2103/tree/collections-framework
 * Last Change:  2016 Oct 20
 ***********************************************************************************/

#ifndef COLLECTIONS_FRAMEWORK_INCLUDE_CONSUMER_H_
#define COLLECTIONS_FRAMEWORK_INCLUDE_CONSUMER_H_

template<class T>
class Consumer {
  public:
    virtual void accept(T& t) = 0;

    virtual Consumer<T>& andThen(Consumer<T>& after) {
        return [this, &after] (T& t) { accept(t); after.accept(t); };
    }
};


#endif  // (COLLECTIONS_FRAMEWORK_INCLUDE_CONSUMER_H_)
