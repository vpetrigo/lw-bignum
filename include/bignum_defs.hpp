#ifndef BIGNUM_DEFS_HPP
#define BIGNUM_DEFS_HPP

#include <vector>

namespace lw_big {
  // base for using with big numbers
  constexpr auto BINBASE = 256;
  constexpr auto BINSHIFT = 8;
  
  // storage for all big numbers in the base 256
  using BigInt = typename std::vector<unsigned>;
  
  // enumeration for numbers' base representation
  enum class base {
    dec,
    bin
  };
  
} // namespace lw_big

#endif // BIGNUM_DEFS_HPP