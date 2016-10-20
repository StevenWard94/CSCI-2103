/***************************************************************************//**
 * Author:       Steven Ward <stevenward94@gmail.com>
 * File:         <repository-root-dir>/collections-framework/src/CollectionExceptions.cpp
 * URL:          https://github.com/StevenWard94/csci-2103/tree/collections-framework
 * Last Change:  2016 Oct 19
 ***************************************************************************/
#include "CollectionExceptions.h"

#include <string.h>

namespace collections {

UnsupportedOperationException::UnsupportedOperationException(std::string const& what_arg)
        : std::runtime_error(what_arg), what_(what_arg.c_str()) { }

UnsupportedOperationException::UnsupportedOperationException(char const* what_arg)
        : std::runtime_error(what_arg), what_(what_arg) { }

char const* UnsupportedOperationException::what( ) const noexcept {
    return this->what_;
}

}
