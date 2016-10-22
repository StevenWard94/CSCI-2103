/**
 * Empty file for now to prevent preprocessor directive errors when attempting to
 * include. May need '#include "Spliterator.h"' in the future if Spliterator class is
 * defined. For now this is just an empty fallback containing only a forward declaration
 * of the class for use with 'std::enable_if<util_lib::has_destructor<Spliterator<T>>>'
 * statements.
 *
 * Incomplete file location:    .../collections-framework/.broken/Spliterator.h
 *
 */

#ifndef COLLECTIONS_FRAMEWORK_INCLUDE_SPLITERATOR_H_
#define COLLECTIONS_FRAMEWORK_INCLUDE_SPLITERATOR_H_

namespace collections {

template<class T>
class Spliterator;

}

#endif  // (COLLECTIONS_FRAMEWORK_INCLUDE_SPLITERATOR_H_)
