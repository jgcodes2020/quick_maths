#ifndef _CMP_MACROS_HPP_
#define _CMP_MACROS_HPP_

/**
 * @brief A hacky macro for providing uniform comparison operators before C++20.
 * @details You need to define operator== and operator< for it to work.
 */
#define _CMP_SAME_TYPE(T)                               \
  friend bool operator>(T a, T b) { return b < a; }     \
  friend bool operator>=(T a, T b) { return !(a < b); } \
  friend bool operator<=(T a, T b) { return !(b < a); } \
  friend bool operator!=(T a, T b) { return !(a == b); }

#endif