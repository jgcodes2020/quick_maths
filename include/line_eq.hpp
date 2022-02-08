#ifndef _LINE_EQ_HPP_
#define _LINE_EQ_HPP_
#include <stdexcept>
#include <variant>
#include "fraction.hpp"
#include "point.hpp"

struct nline_eq {
  fraction m;
  fraction b;
  
  friend std::ostream& operator<<(std::ostream& out, const nline_eq& eq) {
    out << "y = ";
    bool is_m_frac = eq.m.den != 1;
    out << (is_m_frac? "(" : "");
    if (eq.m.sign) out << "-";
    if (eq.m.den > 1 || eq.m.num > 1) out << eq.m.num;
    if (eq.m.den != 1) out << "/" << eq.m.den;
    out << (is_m_frac? ")" : "");
    if (eq.m.num > 0)
      out << "x ";
    fraction bm = std::abs(eq.b);
    out << (eq.b.sign? "- " : "+ ") << bm;
    return out;
  }
};
struct vline_eq {
  fraction x;
  friend std::ostream& operator<<(std::ostream& out, const vline_eq& eq) {
    return out << "x = " << eq.x;
  }
};

using line_eq = std::variant<nline_eq, vline_eq>;

struct no_solutions {};
struct same_line {};
using lin_system_sol = std::variant<no_solutions, point, same_line>;


line_eq two_point_line(point a, point b);

line_eq point_slope(fraction m, point p);

line_eq perp_thru_point(line_eq l, point p);

lin_system_sol solve_system(line_eq a, line_eq b);


inline std::ostream& operator<<(std::ostream& out, const line_eq& v) {
  visit([&](const auto& x) mutable -> void {
    out << x;
  }, v);
  return out;
}
#endif