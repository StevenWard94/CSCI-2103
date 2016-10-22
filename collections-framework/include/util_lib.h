/***********************************************************************************//**
 * Author:       Steven Ward
 * File:         <repository-root-dir>/collections-framework/include/util_lib.h
 * URL:          https://github.com/StevenWard94/csci-2103/tree/collections-framework
 * Last Change:  2016 Oct 21
 ***********************************************************************************/
#ifndef COLLECTIONS_FRAMEWORK_UTILITIES_LIBRARY_H_
#define COLLECTIONS_FRAMEWORK_UTILITIES_LIBRARY_H_

#include <type_traits>

namespace util_lib {

/**
 * The struct template 'has_destructor<T>' exports a boolean constant, 'value', which
 * will be true IFF class 'T' has a public destructor.
 *
 * NOTE: if class 'T' has a non-public destructor and no public destructor, a compile
 * error will occur.
 */
template<class T>
struct has_destructor {

    /** Has public destructor - TRUE */
    template<typename U>
    static std::true_type test( decltype(std::declval<U>().~U()) *) {
        return std::true_type();
    }

    /** Has public destructor - FALSE */
    template<typename U>
    static std::false_type test(...) {
        return std::false_type();
    }

    /** 'type' will be either: 'std::true_type' or 'std::false_type' */
    typedef decltype(test<T>(0)) type;

    static const bool value = type::value;
};

template<class Type, class Test>
using super = typename std::enable_if<std::is_base_of<Test,Type>::value || std::is_same<Test,Type>::value>::type;

template<class Type, class Test>
using extends = typename std::enable_if<std::is_base_of<Type,Test>::value || std::is_same<Type,Test>::value>::type;

template<class Object>
bool isNull(Object obj) {
    return obj == nullptr;
}
}

#endif  // (COLLECTIONS_FRAMEWORK_UTILITIES_LIBRARY_H_)
