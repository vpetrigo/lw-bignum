#ifndef BIGNUM_CONVERTER_HPP
#define BIGNUM_CONVERTER_HPP

#include <iostream>
#include <limits>
#include <algorithm>
#include <sstream>
#include <iterator>
#include <cmath>
#include <cassert>
#include <cstddef>
#include "bignum_defs.hpp"
#include "bignum.hpp"

namespace lw_big {
  class String_to_Dec {
   public:
    using value_type = typename std::vector<unsigned long>;

    static constexpr unsigned DECBASE = 1e7;
    static constexpr unsigned DECBASE_DIGITS = 7;

    static value_type split_string_for_num(const std::string& uinteger) {
      unsigned pos = 0;
      auto int_digits = uinteger.size() / DECBASE_DIGITS;
      auto major_digits_q = uinteger.size() % DECBASE_DIGITS;
      // if we need additional digit for storing major decimal digits
      if (major_digits_q) {
        ++int_digits;
      }
      value_type dec_repr(int_digits);
      auto digits_it = dec_repr.begin();
      *digits_it++ = get_dec_integer(uinteger.substr(pos, major_digits_q));
      pos += major_digits_q;

      while (pos != uinteger.size()) {
        *digits_it++ = get_dec_integer(uinteger.substr(pos, DECBASE_DIGITS));
        pos += DECBASE_DIGITS;
      }

      return dec_repr;
    }

    static unsigned long get_dec_integer(std::string&& str) {
      return std::strtoul(str.c_str(), nullptr, 10);
    }
  };

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

  class To_dec {
  public:
    static constexpr auto HUMAN_DEC_BASE = 10;

    std::string operator()(BigInt&& bint) {
      using BigIntCont_t = typename BigInt::value_type;
      std::stringstream ss;
      std::ostream_iterator<BigIntCont_t> oit{ss};

      naive_base_converter(bint.begin(), bint.end(), oit, BINBASE, HUMAN_DEC_BASE);
      std::string answer{ss.str()};
      std::reverse(answer.begin(), answer.end());

      return answer;
    }
  };

  class Base_Converter {
   public:
    template <typename NumT>
    static BigInt uconvert(NumT num) {
      return uconvert_impl(num,
                    std::is_integral<typename std::remove_reference<NumT>::type>());
    }

    static std::string bconvert(BigInt bint, const base& b) {
      switch (b) {
        case base::bin:
          return {};
        case base::dec:
          To_dec converter;
          return converter(std::move(bint));
      }
    }
   private:
    // Implementation for string
    template <typename NumT>
    static BigInt uconvert_impl(NumT&& num, std::false_type) {
      /* TODO: Deal with "signed" strings */
      auto dec_repr = String_to_Dec::split_string_for_num(num);
      auto storage_size = num.size() / 2 + 1;
      BigInt bint(storage_size);
      std::reverse_iterator<BigInt::iterator> reverse_bint{bint.end()};

      naive_base_converter(dec_repr.begin(), dec_repr.end(), reverse_bint, String_to_Dec::DECBASE, BINBASE);
      remove_lead_zeros(bint);

      return bint;
    }

    // Implementation for integer types
    template <typename NumT>
    static BigInt uconvert_impl(NumT&& num, std::true_type) {
      if (num < 0) {
        num = ~num + 1;
      }

      BigInt bint = get_integral_digits(num);

      // erase leading zeros
      remove_lead_zeros(bint);

      return bint;
    }

    static void remove_lead_zeros(BigInt& bint) {
      bint.erase(bint.begin(), std::find_if(bint.begin(), bint.end() - 1,
                                            [](const BigInt::value_type& e) { return e != 0; }));
    }

    // calculate which size is needed for store integer num
    template <typename NumT>
    static unsigned calc_size_uint(const NumT& num) {
      return static_cast<unsigned> (log(num) / log(256)) + 1;
    }

    // store integer num in the BigInt storage
    template <typename NumT>
    static BigInt get_integral_digits(NumT num) {
      constexpr auto BINMASK = BINBASE - 1;

      BigInt bint(calc_size_uint(num));

      for (auto rit = bint.rbegin(); rit != bint.rend(); ++rit) {
        *rit = num & BINMASK;
        num >>= BINDIGITS;
      }

      assert(num == 0);
      return bint;
    }
  };
} // namespace lw_big

#endif // BIGNUM_CONVERTER_HPP
