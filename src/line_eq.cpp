#include "line_eq.hpp"
#include <optional>
#include <variant>

namespace {
  
}

line_eq two_point_line(point a, point b) {
  if (a.x != b.x) {
    nline_eq res;
    res.m = (a.y - b.y) / (a.x - b.x);
    res.b = b.y - res.m * b.x;
    return res;
  }
  else {
    return vline_eq {b.x};
  }
}
line_eq point_slope(fraction m, point p) {
  nline_eq res;
  res.m = m;
  res.b = p.y - m * p.x;
  return res;
}

line_eq perp_thru_point(line_eq l, point p) {
  struct {
    std::optional<fraction> operator()(const nline_eq& eq) {
      if (eq.m == 0) 
        return std::nullopt;
      return -eq.m.rcp();
    }
    std::optional<fraction> operator()(const vline_eq& eq) {
      return fraction {0};
    }
  } visitor;
  std::optional<fraction> slope = std::visit(visitor, l);
  if (!slope) {
    return vline_eq {p.x};
  }
  return point_slope(*slope, p);
}

lin_system_sol solve_system(line_eq a, line_eq b) {
  struct {
    lin_system_sol operator()(const nline_eq& a, const nline_eq& b) {
      if (a.m == b.m) {
        if (a.b == b.b) {
          return same_line {};
        }
        return no_solutions {};
      }
      fraction px = (b.b - a.b) / (a.m - b.m);
      fraction py = a.m * px + a.b;
      return point {px, py};
    }
    lin_system_sol operator()(const nline_eq& a, const vline_eq& b) {
      fraction py = a.m * b.x + a.b;
      return point {b.x, py};
    }
    lin_system_sol operator()(const vline_eq& a, const nline_eq& b) {
      return (*this)(b, a);
    }
    lin_system_sol operator()(const vline_eq& a, const vline_eq& b) {
      if (a.x == b.x) {
        return same_line {};
      }
      return no_solutions {};
    }
  } visitor;
  return std::visit(visitor, a, b);
}