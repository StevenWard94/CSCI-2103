/***********************************************************************************//**
 * Author:       Steven Ward <stevenward94@gmail.com>
 * File:         <repository-root-dir>/collections-framework/src/AssertionError.cpp
 * URL:          https://github.com/StevenWard94/csci-2103/tree/collections-framework
 * Last Change:  2016 Oct 20
 ***********************************************************************************/

#include "Exceptions.h"

AssertionError::AssertionError(std::string const& what_arg)
        : std::logic_error(what_arg), what_(what_arg.c_str()) { }

AssertionError::AssertionError(char const* what_arg)
        : std::logic_error(what_arg), what_(what_arg) { }

char const* AssertionError::what( ) const noexcept { return this->what_; }
