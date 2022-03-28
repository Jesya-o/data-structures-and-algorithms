#include <numeric>
#include <iostream>
#include "rational.h"

void Rational::DeleteNums(int64_t &up, int64_t &down) {
  int64_t divider = std::gcd(up, down);
  up /= divider;
  down /= divider;
}
void Rational::ReduceFraction(int64_t &up, int64_t &down) {
  if (down == 0) {
    throw RationalDivisionByZero();
  }
  FixSigns(up, down);
  DeleteNums(up, down);
}
void Rational::FixSigns(int64_t &up, int64_t &down) {
  if (down > 0) {
    return;
  }
  if (down < 0) {
    up = -up;
    down = -down;
  }
}

Rational::Rational(int single) {
  numerator = single;
  denominator = 1;
}
Rational::Rational(int64_t up, int64_t down) {
  if (down == 0) {
    throw RationalDivisionByZero();
  }
  ReduceFraction(up, down);
  numerator = up;
  denominator = down;
}
Rational::Rational(const Rational &other) {
  if (other.denominator == 0) {
    throw RationalDivisionByZero{};
  }
  numerator = other.numerator;
  denominator = other.denominator;
  ReduceFraction(numerator, denominator);
}

int64_t Rational::GetNumerator() const {
  return numerator;
}
int64_t Rational::GetDenominator() const {
  return denominator;
}

void Rational::SetNumerator(int64_t up) {
  numerator = up;
  ReduceFraction(numerator, denominator);
}
void Rational::SetDenominator(int64_t down) {
  if (down == 0) {
    throw RationalDivisionByZero{};
  }
  denominator = down;
  ReduceFraction(numerator, denominator);
}

Rational &Rational::operator+=(const Rational &other) {
  numerator = numerator * other.denominator + other.numerator * denominator;
  denominator *= other.denominator;
  ReduceFraction(numerator, denominator);
  return *this;
}
Rational &Rational::operator-=(const Rational &other) {
  numerator = numerator * other.denominator - other.numerator * denominator;
  denominator *= other.denominator;
  ReduceFraction(numerator, denominator);
  return *this;
}
Rational &Rational::operator*=(const Rational &other) {
  numerator *= other.numerator;
  denominator *= other.denominator;
  ReduceFraction(numerator, denominator);
  return *this;
}
Rational &Rational::operator/=(const Rational &other) {
  if (other.numerator == 0) {
    throw RationalDivisionByZero{};
  }
  numerator *= other.denominator;
  denominator *= other.numerator;
  ReduceFraction(numerator, denominator);
  return *this;
}

Rational operator+(const Rational &rational, const Rational &other) {
  Rational num = rational;
  num += other;
  return num;
}
Rational operator-(const Rational &rational, const Rational &other) {
  Rational num = rational;
  num -= other;
  return num;
}
Rational operator*(const Rational &rational, const Rational &other) {
  Rational num = rational;
  num *= other;
  return num;
}
Rational operator/(const Rational &rational, const Rational &other) {
  Rational num = rational;
  num /= other;
  return num;
}

Rational Rational::operator+() const {
  return {numerator, denominator};
}
Rational Rational::operator-() const {
  Rational new_num(-numerator, denominator);
  return new_num;
}

Rational &Rational::operator++() {
  numerator += denominator;
  return *this;
}
Rational &Rational::operator--() {
  numerator -= denominator;
  return *this;
}
Rational Rational::operator++(int) {
  Rational tmp(numerator, denominator);
  ++(*this);
  return tmp;
}
Rational Rational::operator--(int) {
  Rational tmp(numerator, denominator);
  --(*this);
  return tmp;
}

bool operator==(const Rational &rational, const Rational &other) {
  return !(rational < other) && !(other < rational);
}
bool operator!=(const Rational &rational, const Rational &other) {
  return !(rational == other);
}
bool operator<(const Rational &rational, const Rational &other) {
  return rational.numerator * other.denominator < other.numerator * rational.denominator;
}
bool operator>(const Rational &rational, const Rational &other) {
  return other < rational;
}
bool operator<=(const Rational &rational, const Rational &other) {
  return rational < other || rational == other;
}
bool operator>=(const Rational &rational, const Rational &other) {
  return other < rational || rational == other;
}

std::ostream &operator<<(std::ostream &os, const Rational &num) {
  if (num.denominator == 1) {
    os << num.numerator;
  } else {
    os << num.numerator << '/' << num.denominator;
  }
  return os;
}
std::istream &operator>>(std::istream &is, Rational &num) {
  is >> num.numerator;
  if (is.peek() == '/') {
    is.ignore(1);
    is >> num.denominator;
  } else {
    num.denominator = 1;
  }
  if (num.denominator == 0) {
    throw RationalDivisionByZero();
  }
  if (num.denominator < 0) {
    num.numerator = -num.numerator;
    num.denominator = -num.denominator;
  }
  int64_t divider = std::gcd(num.numerator, num.denominator);
  num.numerator /= divider;
  num.denominator /= divider;
  return is;
}
