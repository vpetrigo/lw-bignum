#include <cstddef>
#include <algorithm>
#include "bignum.hpp"
#include "bignum_defs.hpp"

namespace lw_big {
Bignum::Bignum(BigInt&& b) : storage{b} {};

Bignum::~Bignum() {}

// Construct unsigned big integer either from string or unsigned integer
UBignum::UBignum(const std::string& num)
    : Bignum(Base_Converter::uconvert(num)) {}
UBignum::UBignum(const unsigned long long num)
    : Bignum(Base_Converter::uconvert(num)) {}

std::string UBignum::repr(const base& b) const {
  return Base_Converter::bconvert(storage, b);
}

UBignum& UBignum::operator+=(const UBignum& rhs) {
  this->add(rhs.storage);
  
  return *this;
}

const UBignum UBignum::operator+(const UBignum& rhs) const {
  return UBignum(*this) += rhs;
}

void UBignum::add(const BigInt& b) noexcept {
  // determine size needed for storing the result
  auto diff = 0;
  if (b.size() > storage.size()) {
    diff = b.size() - storage.size();
  }
  BigInt lead_zeros(diff + 1, 0);
  storage.insert(storage.begin(), lead_zeros.begin(), lead_zeros.end());

  unsigned short remainder = 0;
  auto a_rev_it = storage.rbegin();
  auto b_rev_it = b.crbegin();
  auto b_rev_end = b.crend();
  
  while (b_rev_it != b_rev_end) {
    auto result = *b_rev_it + *a_rev_it + remainder;
    
    *a_rev_it = result % BINBASE;
    remainder = result / BINBASE;
    ++a_rev_it;
    ++b_rev_it;
  }
  
  if (remainder) {
    *a_rev_it = remainder;
  }
  else {
    storage.erase(storage.begin());
  }
}

}  // namespace lw_big