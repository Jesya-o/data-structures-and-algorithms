#define CATCH_CONFIG_MAIN
#include <catch.hpp>

#include "string_view.h"
#include "string_view.h"  // check include guards

void Equal(const String& actual, const char* expected, size_t n) {
  REQUIRE(actual.Data() == expected);
  REQUIRE(actual.Size() == n);
  REQUIRE(actual.Length() == n);
  REQUIRE(actual.Empty() == (n == 0));
  for (size_t i = 0; i < n; ++i) {
    REQUIRE(actual[i] == expected[i]);
  }
}

TEST_CASE("Default", "[Constructor]") {
  const String sv;
  Equal(sv, nullptr, 0);
}

TEST_CASE("From C String", "[Constructor]") {
  const char* str = "aba";
  const String sv = str;
  Equal(sv, str, 3);
}

TEST_CASE("From C Substring", "[Constructor]") {
  const char* str = "abacaba";
  const String sv(str + 2, 4);
  Equal(sv, str + 2, 4);
}

TEST_CASE("Copy", "[Constructor]") {
  const char* str = "abacaba";
  const String sv(str + 2, 4);
  const auto copy = sv;
  Equal(sv, str + 2, 4);
  Equal(copy, str + 2, 4);
}

TEST_CASE("DataAccess", "[Methods]") {
  static_assert(!std::is_assignable_v<decltype(std::declval<String&>().Front()), char>);
  static_assert(!std::is_assignable_v<decltype(std::declval<String&>().Back()), char>);
  static_assert(!std::is_assignable_v<decltype(std::declval<String&>().At(0)), char>);
  static_assert(!std::is_assignable_v<decltype(std::declval<String&>()[0]), char>);

  const String sv = "abcdef";

  REQUIRE(sv.Front() == 'a');
  REQUIRE(sv.Back() == 'f');
  REQUIRE(sv[1] == 'b');
  REQUIRE(sv.At(2) == 'c');
  REQUIRE_THROWS_AS(sv.At(6), StringViewOutOfRange);
}

TEST_CASE("RemovePrefix", "[Modifications]") {
  const char* str = "some_test_string";
  String sv = str;

  sv.RemovePrefix(5);
  Equal(sv, str + 5, 11);

  sv.RemovePrefix(0);
  Equal(sv, str + 5, 11);

  sv.RemovePrefix(4);
  Equal(sv, str + 9, 7);

  sv.RemovePrefix(7);
  Equal(sv, str + 16, 0);
}

TEST_CASE("RemoveSuffix", "[Modifications]") {
  const char* str = "some_test_string";
  String sv = str;

  sv.RemoveSuffix(5);
  Equal(sv, str, 11);

  sv.RemoveSuffix(0);
  Equal(sv, str, 11);

  sv.RemoveSuffix(4);
  Equal(sv, str, 7);

  sv.RemoveSuffix(7);
  Equal(sv, str, 0);
}

TEST_CASE("Substr", "[Modifications]") {
  const char* str = "some_test_string";
  String sv = str;

  Equal(sv.Substr(0, 5), str, 5);
  Equal(sv, str, 16);

  Equal(sv.Substr(0, 16), str, 16);
  Equal(sv, str, 16);

  Equal(sv.Substr(2, 7), str + 2, 7);
  Equal(sv, str, 16);

  Equal(sv.Substr(7, 9), str + 7, 9);
  Equal(sv, str, 16);
}

TEST_CASE("Swap", "[Modifications]") {
  const char* str = "some_test_string";
  String sv = str;
  //Equal(sv.Substr(2, 7), str + 2, 7); right
  //Equal(sv, str + 2, 7); wrong
  sv.Substr(2, 7).Swap(sv);

  Equal(sv, str + 2, 7);
}

#ifdef STRING_VIEW_ITERATORS_IMPLEMENTED

TEST_CASE("MemberTypes", "[String]") {
  static_assert(std::is_same_v<String::ValueType, char>);
  static_assert(std::is_integral_v<String::SizeType>);
  static_assert(std::is_integral_v<String::DifferenceType>);
  static_assert(std::is_same_v<String::Pointer, char*>);
  static_assert(std::is_same_v<String::ConstPointer, const char*>);
  static_assert(std::is_same_v<String::Reference, char&>);
  static_assert(std::is_same_v<String::ConstReference, const char&>);
  static_assert(std::is_base_of_v<std::random_access_iterator_tag,
                                  std::iterator_traits<String::Iterator>::iterator_category>);
  static_assert((std::is_same_v<String::Iterator, decltype(std::declval<String>().begin())>));
  static_assert((std::is_same_v<String::Iterator, decltype(std::declval<String>().end())>));
  static_assert((std::is_same_v<String::ConstIterator, decltype(std::declval<const String>().begin())>));
  static_assert((std::is_same_v<String::ConstIterator, decltype(std::declval<const String>().end())>));
  static_assert((std::is_same_v<String::ConstIterator, decltype(std::declval<String>().cbegin())>));
  static_assert((std::is_same_v<String::ConstIterator, decltype(std::declval<String>().cend())>));
  static_assert((std::is_same_v<String::ReverseIterator, decltype(std::declval<String>().rbegin())>));
  static_assert((std::is_same_v<String::ReverseIterator, decltype(std::declval<String>().rend())>));
  using ConstReverseIterator = String::ConstReverseIterator;
  static_assert((std::is_same_v<ConstReverseIterator, decltype(std::declval<const String>().rbegin())>));
  static_assert((std::is_same_v<ConstReverseIterator, decltype(std::declval<const String>().rend())>));
  static_assert((std::is_same_v<ConstReverseIterator, decltype(std::declval<String>().crbegin())>));
  static_assert((std::is_same_v<ConstReverseIterator, decltype(std::declval<String>().crend())>));
  static_assert(std::is_same_v<String::ReverseIterator, std::reverse_iterator<String::Iterator>>);
  static_assert(std::is_same_v<String::ConstReverseIterator, std::reverse_iterator<String::ConstIterator>>);
}

TEST_CASE("Iterator", "[Iterators]") {
  const char* str = "abcdef";
  String sv = str;

  size_t i = 0;
  for (auto&& x : sv) {
    REQUIRE(i < 6u);
    REQUIRE(x == str[i]);
    ++i;
  }
}

TEST_CASE("ConstIterator", "[Iterators]") {
  const char* str = "abcdef";
  String sv = str;

  size_t i = 0;
  for (auto it = sv.cbegin(), end = sv.cend(); it != end; ++it, ++i) {
    REQUIRE(i < 6u);
    REQUIRE(*it == str[i]);
  }
}

TEST_CASE("ReverseIterator", "[Iterators]") {
  const char* str = "abcdef";
  String sv = str;

  size_t i = 5;
  for (auto it = sv.rbegin(), end = sv.rend(); it != end; ++it, --i) {
    REQUIRE(i < 6u);
    REQUIRE(*it == str[i]);
  }
}

TEST_CASE("ConstReverseIterator", "[Iterators]") {
  const char* str = "abcdef";
  String sv = str;

  size_t i = 5;
  for (auto it = sv.crbegin(), end = sv.crend(); it != end; ++it, --i) {
    REQUIRE(i < 6u);
    REQUIRE(*it == str[i]);
  }
}

#endif  // STRING_VIEW_ITERATORS_IMPLEMENTED
