/***********************************************************************************//**
 * Author:       Steven Ward <stevenward94@gmail.com>
 * File:         csci-2103/Algorithms/src/search_sort.cpp
 * URL:          https://github.com/StevenWard94/csci-2103
 * Last Change:  2016 Nov 13
 ***********************************************************************************/

#include <iostream>
#include <string>
#include <type_traits>
#include <utility>

#include <stddef.h>


namespace utils {

template<class ...> using void_t = void;

template<class Predicate, typename T = void>
using enable_if_t = typename std::enable_if<Predicate::value, T>::type;

template<class Type, typename = void>
struct is_sortable : std::false_type { };

template<class Type>
struct is_sortable<Type, void_t<decltype(std::declval<Type>() < std::declval<Type>())>> : std::true_type { };

} // namespace utils

namespace sort {

template<class T>
typename utils::enable_if_t<utils::is_sortable<T>, T*>
bubble(T* t_array, size_t size) {
    bool madeSwap = true;
    size_t i = 0;
    while (madeSwap) {
        madeSwap = false;
        i++;
        for (size_t j = 0; j < size - i; j++) {
            if (*(t_array + j) > *(t_array + j + 1)) {
                T* fst = t_array + j;
                T* snd = t_array + j + 1;
                std::swap(*fst, *snd);
                ++madeSwap;
            }
        }
    }
    return t_array;
}


template<class OutputIterator>
auto bubble(OutputIterator first, OutputIterator last)
        -> utils::enable_if_t<utils::is_sortable<decltype(*first)>, OutputIterator>
{
    bool madeSwap = true;
    OutputIterator fst = first;
    while (madeSwap) {
        madeSwap = false;
        fst++;
        for (OutputIterator it = fst; it != last; it++) {
            if (*it > *(it + 1)) {
                std::swap(*it, *(it + 1));
                ++madeSwap;
            }
        }
    }
    return first;
}


template<class T>
typename utils::enable_if_t<utils::is_sortable<T>, T*>
selection(T* t_array, size_t size) {

}

} // namespace sort
