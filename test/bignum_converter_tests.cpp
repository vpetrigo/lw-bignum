#include "bignum_converter.hpp"
#include <gtest/gtest.h>

/**
 * Base Converter class's tests
 */
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

TEST(Unsigned_Big_Integer_Converter, check_converter_from_zero) {
  const std::string val{"0"};
  const auto conv_result = lw_big::Base_Converter::uconvert(val);
  const std::string ans{"0"};
  const auto result = lw_big::Base_Converter::bconvert(conv_result, lw_big::base::dec);

  EXPECT_EQ(result.size(), ans.size());
  EXPECT_EQ(result, ans);
}

TEST(Unsigned_Big_Integer_Converter, check_converter_from_small_int) {
  const std::string val{"10"};
  const auto conv_result = lw_big::Base_Converter::uconvert(val);
  const std::string ans{"10"};
  const auto result = lw_big::Base_Converter::bconvert(conv_result, lw_big::base::dec);

  EXPECT_EQ(result.size(), ans.size());
  EXPECT_EQ(result, ans);
}

TEST(Unsigned_Big_Integer_Converter, check_converter_from_big_integer) {
  const std::string val{"9223372036854775807"};
  const auto conv_result = lw_big::Base_Converter::uconvert(val);
  const auto back_conv_result =
      lw_big::Base_Converter::bconvert(conv_result, lw_big::base::dec);

  EXPECT_EQ(val, back_conv_result);
}

TEST(Unsigned_Big_Integer_Converter, check_to_dec_very_big_integer) {
  std::string val(10000, '0');
  val.insert(val.begin(), '1');
  const auto conv_result = lw_big::Base_Converter::uconvert(val);
  const auto back_conv_result =
      lw_big::Base_Converter::bconvert(conv_result, lw_big::base::dec);

  EXPECT_EQ(val, back_conv_result);
}

TEST(Unsigned_Big_Integer_Converter, check_to_bin_zero) {
  constexpr unsigned int val = 0;
  const auto conv_result = lw_big::Base_Converter::uconvert(val);
  const auto back_conv_result =
      lw_big::Base_Converter::bconvert(conv_result, lw_big::base::bin);
  const std::string ans{"0"};

  EXPECT_EQ(ans, back_conv_result);
}

TEST(Unsigned_Big_Integer_Converter, check_to_bin_converter_unsigned_int) {
  constexpr unsigned int val = 255;
  const auto conv_result = lw_big::Base_Converter::uconvert(val);
  const auto back_conv_result =
      lw_big::Base_Converter::bconvert(conv_result, lw_big::base::bin);
  const std::string ans{"11111111"};

  EXPECT_EQ(ans, back_conv_result);
}

TEST(Unsigned_Big_Integer_Converter, check_to_bin_unsigned_long_long) {
  const std::string val{"6546549879876954651"};
  const std::string ans{
      "101101011011010000001000110111000111110011100010010101000011011"};
  const auto conv_result = lw_big::Base_Converter::uconvert(val);
  const auto back_conv_result =
      lw_big::Base_Converter::bconvert(conv_result, lw_big::base::bin);

  EXPECT_EQ(ans.size(), back_conv_result.size());
  for (std::size_t i = 0; i < ans.size(); ++i) {
    ASSERT_EQ(ans[i], back_conv_result[i]);
  }
}

/**
 * String to Dec class's tests
 */
TEST(String_to_Dec_Converter, split_small_string_with_zero) {
  const std::string val{"0"};
  const auto res = lw_big::String_to_Dec::split_string_for_num(val);
  const lw_big::String_to_Dec::value_type ans{0};

  EXPECT_EQ(res.size(), ans.size());
  for (auto i = 0; i < ans.size(); ++i) {
    EXPECT_EQ(res[i], ans[i]);
  }
}

TEST(String_to_Dec_Converter, split_small_string_with_zeros) {
  const std::string val{"0000000"};
  const auto res = lw_big::String_to_Dec::split_string_for_num(val);
  const lw_big::String_to_Dec::value_type ans{0};

  EXPECT_EQ(res.size(), ans.size());
  for (auto i = 0; i < ans.size(); ++i) {
    EXPECT_EQ(res[i], ans[i]);
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

TEST(String_to_Dec_Converter, split_big_string) {
  const std::string val(15, '1');
  const auto res = lw_big::String_to_Dec::split_string_for_num(val);
  const lw_big::String_to_Dec::value_type ans{1, 1111111, 1111111};

  EXPECT_EQ(res.size(), ans.size());
  for (auto i = 0; i < ans.size(); ++i) {
    EXPECT_EQ(res[i], ans[i]);
  }
}

TEST(String_to_Dec_Converter, split_very_big_string) {
  std::string val;

  for (std::size_t i = 0; i < 80; ++i) {
    val.append("1234567");
  }
  val.insert(val.begin(), 2, '9');

  const auto res = lw_big::String_to_Dec::split_string_for_num(val);
  lw_big::String_to_Dec::value_type ans(80, 1234567);
  ans.insert(ans.begin(), 99);

  EXPECT_EQ(res.size(), ans.size());
  for (auto i = 0; i < ans.size(); ++i) {
    ASSERT_EQ(res[i], ans[i]);
  }
}
