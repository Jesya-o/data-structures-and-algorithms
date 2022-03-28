#include <stdexcept>
#pragma once

class RationalDivisionByZero : public std::runtime_error {
 public:
  RationalDivisionByZero() : std::runtime_error("RationalDivisionByZero") {
  }
};

class Rational {
 public:
  int64_t numerator = 0;
  int64_t denominator = 1;
  Rational() = default;
  Rational(int single);  // NOLINT
  Rational(int64_t up, int64_t down);
  Rational(const Rational& other);

  int64_t GetNumerator() const;
  int64_t GetDenominator() const;

  void SetNumerator(int64_t up);
  void SetDenominator(int64_t down);

  Rational& operator+=(const Rational& other);
  Rational& operator-=(const Rational& other);
  Rational& operator*=(const Rational& other);
  Rational& operator/=(const Rational& other);

  Rational operator+() const;
  Rational operator-() const;

  Rational& operator++();
  Rational& operator--();

  Rational operator++(int);
  Rational operator--(int);

  friend std::ostream& operator<<(std::ostream& os, const Rational& num);
  friend std::istream& operator>>(std::istream& is, Rational& num);

  ~Rational() = default;

 private:
  void ReduceFraction(int64_t& up, int64_t& down);
  void DeleteNums(int64_t& up, int64_t& down);
  void FixSigns(int64_t& up, int64_t& down);
};
Rational operator+(const Rational& rational, const Rational& other);
Rational operator-(const Rational& rational, const Rational& other);
Rational operator*(const Rational& rational, const Rational& other);
Rational operator/(const Rational& rational, const Rational& other);

bool operator==(const Rational& rational, const Rational& other);
bool operator!=(const Rational& rational, const Rational& other);
bool operator<(const Rational& rational, const Rational& other);
bool operator>(const Rational& rational, const Rational& other);
bool operator<=(const Rational& rational, const Rational& other);
bool operator>=(const Rational& rational, const Rational& other);