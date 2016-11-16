/***********************************************************************************//**
 * Author:       Steven Ward <stevenward94@gmail.com>
 * File:         csci-2103/Algorithms/src/alt_search_sort.cpp
 * URL:          https://github.com/StevenWard94/csci-2103
 * Last Change:  2016 Nov 15
 ***********************************************************************************/

#include <type_traits>
#include <utility>

#include <stddef.h>

namespace utils {

template<class ...> using void_t = void;

template<class Predicate, class T = void>
using enable_if_t = typename std::enable_if<Predicate::value, T>::type;

template<class T, typename = void>
struct is_ordered_type : std::false_type { };

template<class T>
struct is_ordered_type<T, void_t<decltype(std::declval<T>() < std::declval<T>())>> : std::true_type { };

} // namespace utils


namespace sort {

template<class RandomIt>
auto bubble(RandomIt first, RandomIt last)
        -> utils::enable_if_t<utils::is_ordered_type<decltype(*first)>, void>
{
    bool madeSwap = true;
    auto it_back = last;
    while (madeSwap) {
        madeSwap = false;
        it_back--;
        for (auto it_front = first; it_front != it_back; it_front++) {
            auto tmp = it_front;
            ++tmp;
            if (*tmp < *it_front) {
                std::swap(*tmp, *it_front);
                madeSwap = true;
            }
        }
    }
}

} // namespace sort
