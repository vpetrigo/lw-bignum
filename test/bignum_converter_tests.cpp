#include <gtest/gtest.h>
#include "bignum_converter.hpp"

TEST(Unsigned_Big_Integer_Converter, pass_zero) {
  constexpr unsigned val = 0;
  const lw_big::BigInt ans{0};
  const auto conv_result = lw_big::Base_Converter::uconvert(val);
  
  EXPECT_EQ(conv_result.size(), ans.size());
  EXPECT_EQ(conv_result[0], ans[0]);
}

TEST(Unsigned_Big_Integer_Converter, pass_unsigned_value) {
  constexpr unsigned val = 65486;
  const lw_big::BigInt ans{255, 206};
  const auto conv_result = lw_big::Base_Converter::uconvert(val);
  
  EXPECT_EQ(conv_result.size(), ans.size());
  for (auto i = 0; i < conv_result.size(); ++i) {
    EXPECT_EQ(conv_result[i], ans[i]);
  }
}

TEST(Unsigned_Big_Integer_Converter, pass_signed_value) {
  constexpr int val = 65486;
  const lw_big::BigInt ans{255, 206};
  const auto conv_result = lw_big::Base_Converter::uconvert(val);
  
  EXPECT_EQ(conv_result.size(), ans.size());
  for (auto i = 0; i < conv_result.size(); ++i) {
    EXPECT_EQ(conv_result[i], ans[i]);
  }
}

TEST(Unsigned_Big_Integer_Converter, pass_negative_signed_value) {
  constexpr auto val = -4611686018427387905;
  const lw_big::BigInt ans{64, 0, 0, 0, 0, 0, 0, 1};
  const auto conv_result = lw_big::Base_Converter::uconvert(val);
  
  EXPECT_EQ(conv_result.size(), ans.size());
  for (auto i = 0; i < conv_result.size(); ++i) {
    EXPECT_EQ(conv_result[i], ans[i]);
  }
}

TEST(String_to_Dec_Converter, split_small_string) {
  const std::string val{"10"};
  const auto res = lw_big::String_to_Dec::split_string_for_num(val);
  const lw_big::String_to_Dec::value_type ans{10};
  
  EXPECT_EQ(res.size(), ans.size());
  for (auto i = 0; i < ans.size(); ++i) {
    EXPECT_EQ(res[i], ans[i]);
  }
}

TEST(Unsigned_Big_Integer_Converter, pass_unsigned_string) {
  const std::string val{"0"};
  const lw_big::BigInt ans{0};
  const auto conv_result = lw_big::Base_Converter::uconvert(val);
  
  EXPECT_EQ(conv_result.size(), ans.size());
  for (auto i = 0; i < conv_result.size(); ++i) {
    EXPECT_EQ(conv_result[i], ans[i]);
  }
}

TEST(Unsigned_Big_Integer_Converter, check_string_and_uint_answer) {
  const std::string val1{"9223372036854775807"};
  constexpr auto val2 = 9223372036854775807;
  const lw_big::BigInt ans{127, 255, 255, 255, 255, 255, 255, 255};
  const auto conv_result1 = lw_big::Base_Converter::uconvert(val1);
  const auto conv_result2 = lw_big::Base_Converter::uconvert(val2);
  
  EXPECT_EQ(conv_result1.size(), ans.size());
  EXPECT_EQ(conv_result2.size(), ans.size());
  for (auto i = 0; i < ans.size(); ++i) {
    EXPECT_EQ(conv_result1[i], ans[i]);
    EXPECT_EQ(conv_result2[i], ans[i]);
  }
}