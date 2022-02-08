#ifndef _POINT_HPP_
#define _POINT_HPP_
#include <iostream>
#include "fraction.hpp"

struct point {
  fraction x, y;
  
  friend point operator+(point a, point b) {
    return point {a.x + b.x, a.y + b.y};
  }
  
  friend point operator-(point a, point b) {
    return point {a.x - b.x, a.y - b.y};
  }
  
  friend point operator*(point a, fraction b) {
    return point {a.x * b, a.y * b};
  }
  
  friend point operator*(fraction a, point b) {
    return b * a;
  }
  
  friend point operator/(point a, fraction b) {
    return point {a.x / b, a.y / b};
  }
  
  friend std::ostream& operator<<(std::ostream& out, const point& a) {
    return out << "(" << a.x << ", " << a.y << ")";
  }
  
  fraction dist() {
    
  }
};
#endif