#include <iostream>
#include <array>
#include <algorithm>
#include <cstddef>
#include <cassert>
#include <cstdlib>
#include <cmath>
#include <iterator>

constexpr auto DEC_BASE_DIGITS = 7;
constexpr auto DEC_BASE = 10000000;
constexpr auto BIN_BASE = 256;

using BigInt = typename std::vector<unsigned short>;
using DecInt = typename std::vector<unsigned>;

class int_to_char_inserter : public std::insert_iterator<std::string> {
 public:
  using std::insert_iterator<std::string>::insert_iterator;
  
  template <typename IntT>
  int_to_char_inserter& operator=(IntT num) {
    container->insert(iter, '0' + num);
    ++iter;
    return *this;
  }
  
  int_to_char_inserter& operator*() {
    return *this;
  }
};

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

// handle only unsigned integers now
BigInt dec2bin(const std::string& uinteger) {
  const auto q_digits = uinteger.size();
  BigInt bint(calc_size(q_digits));
  auto dec_repr = split_string_for_num(uinteger);
  const auto dec_repr_size = dec_repr.size();
  const auto dec_repr_last_digit = dec_repr_size - 1;
  std::size_t index = 0;
  auto bin_back_it = bint.end() - 1;
  
  while (index != dec_repr_size) {
    if (dec_repr[index] == 0) {
      ++index;
    }
    
    unsigned rem = 0;
    for (std::size_t i = index; i < dec_repr_size; ++i) {
      auto number = rem * DEC_BASE + dec_repr[i];
      auto cur_rem = number % BIN_BASE;
      
      dec_repr[i] = number / BIN_BASE;
      rem = cur_rem;
      if (i == dec_repr_last_digit) {
        *bin_back_it-- = number % BIN_BASE;
      }
    }
  }
  
  auto lead_zeroes = count_lead_zeroes(bint);
  
  bint.erase(bint.begin(), bint.begin() + lead_zeroes);
  
  return bint;
}

template <typename FromNumContIt, typename ToNumIt>
void naive_division(FromNumContIt begin, FromNumContIt end, ToNumIt to_back, const int from_base, const int to_base) {
  while (begin != end) {
    if (*begin == 0) {
      ++begin;
    }
    
    auto rem = 0ULL;
    for (auto it = begin; it != end; ++it) {
      auto number = rem * from_base + *begin;
      auto cur_rem = number % to_base;
      
      *begin = number / to_base;
      rem = cur_rem;
      if (it == end - 1) {
        *to_back-- = number % to_base;
      }
    }
  }
}

std::string bin2dec(BigInt bin) {
  const auto input_arr_size = bin.size();
  const auto last_digit = input_arr_size - 1;
  auto zero_counter = 0;
  std::size_t index = 0;
  std::string answer;
  
  while (index != input_arr_size) {
    if (bin[index] == 0) {
      ++index;
    }
    
    unsigned rem = 0;
    for (std::size_t i = index; i < input_arr_size; ++i) {
      auto number = (rem << 8) + bin[i];
      auto cur_rem = number % 10;

      bin[i] = number / 10;
      rem = cur_rem;
      if (i == last_digit) {
        answer += std::to_string(number % 10);
      }
    }
  }
  
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
  
  std::string s;
  
  int_to_char_inserter ici(s, s.begin());
  ici = 0;
  ici = 2;
  
  std::cout << s << std::endl;
  
  return 0;
}