#ifndef _FRACTION_HPP_
#define _FRACTION_HPP_

#include <charconv>
#include <cstdint>
#include <iostream>
#include <numeric>
#include <stdexcept>
#include <string>
#include <type_traits>
#include <utility>
#include <csignal>

#include "cmp_macros.hpp"

using std::clog;

struct fraction {
  uint64_t num, den;
  bool sign;
  
  fraction() {}
  
  fraction(uint64_t num, uint64_t den = 1, bool sign = false) :
    num(num), den(den), sign(sign) {}

  fraction& reduce_this() {
    if (num == 0) {
      den  = 1;
      sign = false;
      return *this;
    }

    uint64_t gcd = std::gcd(num, den);
    num /= gcd, den /= gcd;

    return *this;
  }

  fraction rcp() const { return fraction {den, num, sign}; }

  friend fraction operator-(fraction x) {
    return fraction {x.num, x.den, !x.sign && x.num != 0};
  }

  friend fraction operator+(fraction a, fraction b) {
    // don't do multiplication step for equal denominators
    if (a.den == b.den) {
      // if same sign, will add up
      if (a.sign == b.sign)
        return fraction {a.num + b.num, a.den, b.sign}.reduce_this();

      // if different sign, will subtract
      bool passes_zero = b.num > a.num;
      return fraction {
        passes_zero ? b.num - a.num : a.num - b.num, a.den,
        a.sign != passes_zero}
        .reduce_this();
    }
    else {
      // Find a common denominator
      uint64_t new_den  = a.den * b.den;
      uint64_t new_anum = a.num * b.den;
      uint64_t new_bnum = b.num * a.den;
      // same idea as above
      if (a.sign == b.sign)
        return fraction {new_anum + new_bnum, new_den}.reduce_this();

      bool passes_zero = new_bnum > new_anum;
      return fraction {
        passes_zero ? new_bnum - new_anum : new_anum - new_bnum, new_den,
        a.sign != passes_zero}
        .reduce_this();
    }
  }

  friend fraction operator-(fraction a, fraction b) {
    // This is what you were taught when learning integers
    return a + -b;
  }

  friend fraction operator*(fraction a, fraction b) {
    // note that logical xor works
    return fraction {a.num * b.num, a.den * b.den, a.sign != b.sign}
      .reduce_this();
  }

  friend fraction operator/(fraction a, fraction b) {
    if (b.num == 0) raise(SIGFPE);
    // inverts a fraction to yield diviion
    return a * b.rcp();
  }

  operator double() { return static_cast<double>(this->num) / this->den; }

  friend std::ostream& operator<<(std::ostream& out, const fraction& x) {
    out << (x.sign ? "-" : "") << x.num;
    if (x.den > 1) {
      out << "/" << x.den;
    }
    return out;
  }

  friend std::istream& operator>>(std::istream& in, fraction& x) {
    uint64_t num, den;
    bool sign;

    std::string word;
    size_t end = 0;
    in >> word;
    if (word[end] == '-') {
      sign = true;
      ++end;
    }
    num = std::stoi(word.substr(end), &end, 10);
    if (end == word.size()) {
      x = {num, 1, sign};
      return in;
    }
    else if (word[end] != '/') {
      in.setstate(std::ios_base::failbit);
      x = {0, 1};
      return in;
    }
    den = std::stoi(word.substr(++end), &end, 10);
    if (end == word.size()) {
      x = {num, den, sign};
      return in;
    }
    in.setstate(std::ios_base::failbit);
    x = {0, 1};
    return in;
  }
  
  friend bool operator==(fraction a, fraction b) {
    a.reduce_this();
    b.reduce_this();
    
    return a.num == b.num && a.den == b.den;
  }
  
  friend bool operator<(fraction a, fraction b) {
    a.reduce_this();
    b.reduce_this();
    
    uint64_t num_a = a.num * b.den;
    uint64_t num_b = b.num * a.den;
    
    return num_a < num_b;
  }

  _CMP_SAME_TYPE(fraction)
  
  static fraction parse(std::string word) {
    uint64_t num, den;
    bool sign = false;
    fraction x;
    size_t end = 0;
    if (word[end] == '-') {
      ++end;
      sign = true;
    }
    word = word.substr(end);
    num = std::stoull(word, &end, 10);
    if (end == word.size()) {
      return {num, 1, sign};
    }
    else if (word[end] != '/') {
      throw std::invalid_argument("Not a fraction");
    }
    word = word.substr(++end);
    den = std::stoi(word, &end, 10);
    
    if (end == word.size()) {
      return {num, den, sign};
    }
    throw std::invalid_argument("Not a fraction");
  }
};

namespace std {
  inline fraction abs(const fraction& x) {
    return fraction {x.num, x.den, false};
  }
}

#endif