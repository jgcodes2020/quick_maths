#include <iostream>
#include <cstring>
#include <variant>
#include "fraction.hpp"
#include "point.hpp"
#include "line_eq.hpp"

using std::cout, std::cerr, std::endl, std::flush;

point centroid(point a, point b, point c) {
  return (a + b + c) / 3;
}

line_eq median(point a, point b, point c) {
  point mid = (a + b) / 2;
  return two_point_line(mid, c);
}

line_eq altitude(point a, point b, point c) {
  return perp_thru_point(two_point_line(a, b), c);
}

line_eq perp_bisector(point a, point b) {
  return perp_thru_point(two_point_line(a, b), (a + b) / 2);
}

point orthocenter(point a, point b, point c) {
  auto res = solve_system(altitude(a, b, c), altitude(b, c, a));
  return std::get<point>(res);
}

point circumcenter(point a, point b, point c) {
  auto res = solve_system(perp_bisector(a, b), perp_bisector(b, c));
  return std::get<point>(res);
}

int main(const int argc, const char* argv[]) {
  if (argc != 8) {
    cerr << "Need 7 arguments.\n";
    cerr << argv[0] << " [op] [xa] [ya] [xb] [yb] [xc] [yc]\n";
  }
  
  point a = {fraction::parse(argv[2]), fraction::parse(argv[3])};
  point b = {fraction::parse(argv[4]), fraction::parse(argv[5])};
  point c = {fraction::parse(argv[6]), fraction::parse(argv[7])};
  
  
  cout << "Triangle points: " << a << "; " << b << "; " << c << endl;
  if (strcmp("med", argv[1]) == 0) {
    cout << "Midpoint AB: " << (a + b) / 2 << endl;
    cout << "Midpoint BC: " << (b + c) / 2 << endl;
    cout << "Midpoint AC: " << (a + c) / 2 << "\n\n" << flush;
    
    cout << "Median AB-C: " << median(a, b, c) << endl;
    cout << "Median BC-A: " << median(b, c, a) << endl;
    cout << "Median AC-B: " << median(a, c, b) << endl;
    
    cout << "Centroid: " << centroid(a, b, c) << endl;
  }
  else if (strcmp("alt", argv[1]) == 0) {
    cout << "Altitude AB-C: " << altitude(a, b, c) << endl;
    cout << "Altitude BC-A: " << altitude(b, c, a) << endl;
    cout << "Altitude AC-B: " << altitude(a, c, b) << endl;
    
    cout << "Orthocenter: " << orthocenter(a, b, c) << endl;
  }
  else if (strcmp("pbi", argv[1]) == 0) {
    cout << "Midpoint AB: " << (a + b) / 2 << endl;
    cout << "Midpoint BC: " << (b + c) / 2 << endl;
    cout << "Midpoint AC: " << (a + c) / 2 << "\n\n" << flush;
    
    cout << "Perp. bisector AB: " << perp_bisector(a, b) << endl;
    cout << "Perp. bisector BC: " << perp_bisector(b, c) << endl;
    cout << "Perp. bisector AC: " << perp_bisector(a, c) << endl;
    
    cout << "Circumcenter: " << circumcenter(a, b, c) << endl;
  }
}