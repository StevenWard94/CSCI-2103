/***************************************************************************//**
 * Author:       Steven Ward
 * File:         <repository-root-dir>/collections-framework/include/CollectionExceptions.h
 * URL:          https://github.com/StevenWard94/csci-2103/tree/collections-framework
 * Last Change:  2016 Oct 19
 ***************************************************************************/
#ifndef COLLECTIONS_FRAMEWORK_INCLUDE_COLLECTION_EXCEPTIONS_H_
#define COLLECTIONS_FRAMEWORK_INCLUDE_COLLECTION_EXCEPTIONS_H_

#include <stdexcept>
#include <string>

namespace collections {

class UnsupportedOperationException : public std::runtime_error {
  public:
    inline UnsupportedOperationException( ) : std::runtime_error(""), what_("") { }
    explicit UnsupportedOperationException(std::string const& );
    explicit UnsupportedOperationException(char const* );

    char const* what( ) const noexcept override;

  private:
    char const* what_;
};
}

#endif  // (COLLECTIONS_FRAMEWORK_INCLUDE_COLLECTION_EXCEPTIONS_H_)
