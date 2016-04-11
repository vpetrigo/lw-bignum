#include "bignum.hpp"
#include <gtest/gtest.h>

TEST(Unsigned_Big_Numbers, construct_unsigned_big_number_from_int) {
  lw_big::UBignum a{123};
  const std::string ans{"123"};
  
  EXPECT_EQ(ans, a.repr(lw_big::base::dec));
}

TEST(Unsigned_Big_Numbers, construct_unsigned_big_number_from_string) {
  lw_big::UBignum a{"123"};
  const std::string ans{"123"};
  
  EXPECT_EQ(ans, a.repr(lw_big::base::dec));
}

TEST(Unsigned_Big_Numbers, construct_unsigned_big_number_from_int_to_bin) {
  lw_big::UBignum a{123};
  const std::string ans{"1111011"};
  
  EXPECT_EQ(ans, a.repr(lw_big::base::bin));
}

TEST(Unsigned_Big_Numbers, construct_unsigned_big_number_from_string_to_bin) {
  lw_big::UBignum a{"123"};
  const std::string ans{"1111011"};
  
  EXPECT_EQ(ans, a.repr(lw_big::base::bin));
}

TEST(Unsigned_Big_Numbers, assignment_with_addition_test) {
  lw_big::UBignum a{"123"};
  lw_big::UBignum b{"321"};
  const std::string ans{"444"};
  
  a += b;
  
  EXPECT_EQ(ans, a.repr(lw_big::base::dec));
}

TEST(Unsigned_Big_Numbers, assignment_with_addition_test2) {
  lw_big::UBignum a{9223372036854775807};
  lw_big::UBignum b{"9223372036852678655"};
  const std::string ans{"18446744073707454462"};
  
  a += b;
  
  EXPECT_EQ(ans, a.repr(lw_big::base::dec));
}

TEST(Unsigned_Big_Numbers, addition_operator_test) {
  const lw_big::UBignum a{9223372036854775807};
  const lw_big::UBignum b{"9223372036852678655"};
  const std::string ans{"18446744073707454462"};
  const auto c = a + b;
  
  EXPECT_EQ(ans, c.repr(lw_big::base::dec));
}