#include <iostream>
#include <array>
#include <algorithm>
#include <cstddef>
#include <cassert>
#include <cstdlib>
#include <cmath>
#include <iterator>
#include <sstream>

constexpr auto DEC_BASE_DIGITS = 7;
constexpr auto DEC_BASE = 10000000;
constexpr auto HUMAN_DEC_BASE = 10;
constexpr auto BIN_BASE = 256;

using BigInt = typename std::vector<unsigned short>;
using DecInt = typename std::vector<unsigned>;

template <typename SizeT>
SizeT calc_size(SizeT size) {
  return (size >> 1);
}

unsigned long get_dec_integer(std::string&& str) {
  return std::strtoul(str.c_str(), nullptr, 10);
}

std::size_t count_lead_zeroes(const BigInt& num) {
  std::size_t counter = 0;

  for (auto cit = num.cbegin(); cit != num.cend() && *cit == 0; ++cit) {
    ++counter;
  }

  return counter;
}

DecInt split_string_for_num(const std::string& uinteger) {
  unsigned pos = 0;
  auto int_digits = uinteger.size() / DEC_BASE_DIGITS;
  auto major_digits_q = uinteger.size() - DEC_BASE_DIGITS * int_digits;
  DecInt dec_repr(int_digits + 1);
  auto digits_it = dec_repr.begin();

  *digits_it++ = get_dec_integer(uinteger.substr(pos, major_digits_q));
  pos += major_digits_q;

  while (pos != uinteger.size()) {
    *digits_it++ = get_dec_integer(uinteger.substr(pos, DEC_BASE_DIGITS));
    pos += DEC_BASE_DIGITS;
  }

  return dec_repr;
}

template <typename FromNumContIt, typename ToNumIt>
void naive_base_converter(FromNumContIt begin, FromNumContIt end, ToNumIt to_back,
                    const int from_base, const int to_base) {
  while (begin != end) {
    if (*begin == 0) {
      ++begin;
    }

    auto rem = 0ULL;
    for (auto it = begin; it != end; ++it) {
      auto number = rem * from_base + *it;
      auto cur_rem = number % to_base;

      *it = number / to_base;
      rem = cur_rem;
      if (it == end - 1) {
        *to_back++ = cur_rem;
      }
    }
  }
}

// handle only unsigned integers now
BigInt dec2bin(const std::string& uinteger) {
  using BigIntIter_t = typename BigInt::iterator;
  const auto q_digits = uinteger.size();
  BigInt bint(calc_size(q_digits));
  auto dec_repr = split_string_for_num(uinteger);
  std::reverse_iterator<BigIntIter_t> reverse_bint{bint.end()};

  naive_base_converter(dec_repr.begin(), dec_repr.end(), reverse_bint, DEC_BASE, BIN_BASE);
  auto lead_zeroes = count_lead_zeroes(bint);

  bint.erase(bint.begin(), bint.begin() + lead_zeroes);

  return bint;
}

std::string bin2dec(BigInt bin) {
  using BigIntCont_t = typename BigInt::value_type;
  std::stringstream ss;
  std::ostream_iterator<BigIntCont_t> oit{ss};

  naive_base_converter(bin.begin(), bin.end(), oit, BIN_BASE, HUMAN_DEC_BASE);

  std::string answer{ss.str()};
  std::reverse(answer.begin(), answer.end());

  return answer;
}

int main() {
  BigInt arr{64, 32, 0, 18, 8, 16, 0, 0};
  std::string ans{"4620693295126806528"};
  auto function_ans = bin2dec(arr);

  std::cout << function_ans << std::endl;
  assert(ans == function_ans);

  BigInt arr2{3, 231};

  std::cout << bin2dec(arr2) << std::endl;

  std::string test{"4620693295126806528"};
  auto res = dec2bin(test);

  assert(test == bin2dec(res));

  return 0;
}
