#ifndef BIGNUM_HPP
#define BIGNUM_HPP

#include <string>
#include "bignum_converter.hpp"
#include "bignum_defs.hpp"

namespace lw_big {

class Bignum {
 public:
  Bignum() = delete;
  
  virtual std::string repr(const base& b) const = 0;
  virtual ~Bignum();

 protected:
  Bignum(BigInt&& b);

  BigInt storage;
};

class UBignum : public Bignum {
 public:
  // TODO: initialize big number with a string
  // string might represent a number either in decimal format or binary
  // example: "12345" - dec; "001001" - bin;
  explicit UBignum(const std::string& num);
  // initialize big number with a unsigned integer
  explicit UBignum(const unsigned long long num);
  
  UBignum& operator+=(const UBignum& rhs);
  const UBignum operator+(const UBignum& rhs) const;
  UBignum& operator-=(const UBignum& rhs);
  const UBignum operator-(const UBignum& rhs) const;
  UBignum& operator*=(const UBignum& rhs);
  const UBignum operator*(const UBignum& rhs) const;
  UBignum& operator/=(const UBignum& rhs);
  const UBignum operator/(const UBignum& rhs) const;

  std::string repr(const base& b) const;
  
  private:
    void add(const BigInt& b);
};

}  // namespace lw_big

#endif  // BIGNUM_HPP