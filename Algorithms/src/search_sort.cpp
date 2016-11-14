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

template<class Type, typename = void>
struct is_sortable : std::false_type { };

template<class Type>
struct is_sortable<Type, void_t<decltype(std::declval<Type>() < std::declval<Type>())>> : std::true_type { };

} // namespace utils

namespace sort {

template <class T, class = typename std::enable_if<utils::is_sortable<T>::value>::type>
T* bubble(T* t_array, size_t size) {
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

} // namespace sort
