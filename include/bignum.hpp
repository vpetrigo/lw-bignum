#ifndef BIGNUM_HPP
#define BIGNUM_HPP

#include <string>
#include "bignum_defs.hpp"
#include "bignum_converter.hpp"

namespace lw_big {
  
  class Bignum {
    public:
      virtual std::string repr(base& b) = 0;
      virtual ~Bignum();
    protected:
      Bignum();
    private:
      BigInt storage;
  };
  
  class UBignum : public Bignum {
    public:
      UBignum();
      // initialize big number with a string
      // string might represent a number either in decimal format or binary
      // example: "12345" - dec; "001001" - bin;
      UBignum(const std::string& num, const base& b);
      // initialize big number with a unsigned integer
      template <typename UnsignedT>
      UBignum(const UnsignedT num);
      
      std::string repr(base& b);
  };
  
} // namespace lw_big

#endif // BIGNUM_HPP