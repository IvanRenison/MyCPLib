#pragma once

#include <IncludeTemplate.hpp>

struct Ratio {
  ll num;
  ull den;
  Ratio(ll num = 0, ull den = 1) {
    ull g = gcd((ull)abs(num), den);
    this->num = num / ((ll)g);
    this->den = den / g;
  }

  Ratio operator+(Ratio o) const {
    ull new_den = den * o.den;
    ll new_num = num * (ll)o.den + o.num * (ll)den;
    return Ratio(new_num, new_den);
  }
  Ratio operator-(Ratio o) const {
    ull new_den = den * o.den;
    ll new_num = num * (ll)o.den - o.num * (ll)den;
    return Ratio(new_num, new_den);
  }
  Ratio operator*(Ratio o) const {
    return Ratio(num * o.num, den * o.den);
  }
  Ratio operator/(Ratio o) const {
    assert(o.num != 0);
    return Ratio(num * (ll)o.den * signum(o), den * abs(o.num));
  }

  void operator+=(Ratio o) {
    *this = *this + o;
  }
  void operator-=(Ratio o) {
    *this = *this - o;
  }
  void operator*=(Ratio o) {
    *this = *this * o;
  }
  void operator/=(Ratio o) {
    *this = *this / o;
  }

  bool operator==(Ratio o) const {
    return num == o.num && den == o.den;
  }
  bool operator!=(Ratio o) const {
    return !(*this == o);
  }
  bool operator<(Ratio o) const {
    return num * (ll)o.den < o.num * (ll)den;
  }
  bool operator<=(Ratio o) const {
    return *this < o || *this == o;
  }
  bool operator>(Ratio o) const {
    return o < *this;
  }
  bool operator>=(Ratio o) const {
    return o <= *this;
  }

  friend ostream& operator<<(ostream& os, Ratio r) {
    os << r.num;
    if (r.den != 1) {
      os << "/" << r.den;
    }
    return os;
  }
};

ll signum(Ratio n) {
  return signum(n.num);
}
