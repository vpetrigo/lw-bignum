#include "bignum.hpp"
#include <algorithm>
#include <cstddef>
#include <iostream>
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
  this->add(rhs.storage, add_carry::yes);

  return *this;
}

const UBignum UBignum::operator+(const UBignum& rhs) const {
  return UBignum(*this) += rhs;
}

UBignum& UBignum::operator-=(const UBignum& rhs) {
  this->substr(rhs.storage);

  return *this;
}

const UBignum UBignum::operator-(const UBignum& rhs) const {
  return UBignum(*this) -= rhs;
}

void UBignum::add(const BigInt& b, const add_carry& ac) noexcept {
  // determine size needed for storing the result
  auto diff = 0;
  if (b.size() > storage.size()) {
    diff = b.size() - storage.size();
  }
  BigInt lead_zeros(diff + 1, 0);
  storage.insert(storage.begin(), lead_zeros.begin(), lead_zeros.end());

  unsigned short rem = 0;
  auto a_rev_it = storage.rbegin();
  auto b_rev_it = b.crbegin();
  auto b_rev_end = b.crend();

  while (b_rev_it != b_rev_end) {
    auto result = *b_rev_it + *a_rev_it + rem;

    *a_rev_it = result % BINBASE;
    rem = result / BINBASE;
    ++a_rev_it;
    ++b_rev_it;
  }

  // if we still have remainder just pass through all digits and try to add
  // remainder
  // in case of overflow of current BINBASE in a digit, set it to zero and go
  // further
  if (rem) {
    while ((*a_rev_it + rem) % BINBASE == 0) {
      *a_rev_it++ = 0;
    }
    *a_rev_it += rem;
  }

  if (!storage.front() || ac == add_carry::no) {
    storage.erase(storage.begin());
  }
}

void UBignum::substr(const BigInt& b) noexcept {
  // a - b = a + (-b + 1)
  auto max_size = std::max(storage.size(), b.size());
  // for storing '-b'
  BigInt neg_b(max_size);
  // + 1
  BigInt one{1};

  std::copy(b.crbegin(), b.crend(), neg_b.rbegin());
  // do b = -b
  std::transform(neg_b.begin(), neg_b.end(), neg_b.begin(),
                 [](const BigInt::value_type& e) { return ~e % BINBASE; });
  add(neg_b, add_carry::no);
  add(one, add_carry::no);
}

}  // namespace lw_big
