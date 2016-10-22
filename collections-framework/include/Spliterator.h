/***********************************************************************************//**
 * Author:       Steven Ward <stevenward94@gmail.com>
 * File:         <repository-root-dir>/collections-framework/include/Spliterator.h
 * URL:          https://github.com/StevenWard94/csci-2103/tree/collections-framework
 * Last Change:  2016 Oct 21
 ***********************************************************************************/

#ifndef COLLECTIONS_FRAMEWORK_INCLUDE_SPLITERATOR_H_
#define COLLECTIONS_FRAMEWORK_INCLUDE_SPLITERATOR_H_

#include "Consumer.h"

#include <cstdint>
#include <type_traits>

namespace collections {

template<class T>
class Spliterator {
  public:
    static const std::int32_t ORDERED    = 0x00000010;
    static const std::int32_t DISTINCT   = 0x00000001;
    static const std::int32_t SORTED     = 0x00000004;
    static const std::int32_t SIZED      = 0x00000040;
    static const std::int32_t NONNULL    = 0x00000100;
    static const std::int32_t IMMUTABLE  = 0x00000400;
    static const std::int32_t CONCURRENT = 0x00001000;
    static const std::int32_t SUBSIZED   = 0x00004000;

    // ERROR: TEMPLATE CANNOT BE VIRTUAL - JAVA DEFINES NO DEFAULT IMPLEMENTATION
    //template<class D,enable_if< is_base_of<D,T> || is_same<D,T> >::type>
    //virtual bool tryAdvance(Consumer<D> action) = 0;
    virtual bool tryAdvance(Consumer<T>& action) = 0;

    template< class D
            , typename =
                typename std::enable_if<std::is_base_of<D,T>::value || std::is_same<D,T>::value>::type
            >
    void forEachRemaining(Consumer<D> action) {
        do { } while ( tryAdvance(action) );
    }

    virtual Spliterator<T>& trySplit( ) = 0;

    virtual std::int64_t estimateSize( ) = 0;

    virtual std::int64_t getExactSizeIfKnown( ) {
        return (characteristics() & SIZED) == 0 ? -1L : estimateSize();
    }

    virtual std::int32_t characteristics( ) = 0;

    virtual bool hasCharacteristics(std::int32_t characteristics) {
        return (characteristics() & characteristics) == characteristics;
    }
};
}

#endif  // (COLLECTIONS_FRAMEWORK_INCLUDE_SPLITERATOR_H_)
