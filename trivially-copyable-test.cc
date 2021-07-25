#include <complex>
#include <iomanip>
#include <iostream>
#include <string_view>
#include <type_traits>

#include "type_name.hh"

struct S {};
class C1 {};
class C2 { virtual ~C2() = default; };
class D1 : C1 {};
class D2 : virtual C1 {};

template <class T>
void report_tc()
{
  std::cout << "type "
            << type_name<T>() 
            << " is trivally copyable? "
            << std::boolalpha
            << std::is_trivially_copyable_v<T>
            << '\n';
}

template <class T>
void report_tc(T const&)
{
  report_tc<T>();
}

int main()
{
  report_tc<std::string_view>();
  report_tc<std::complex<double>>();
  report_tc<std::string>();
  report_tc<S>();
  report_tc<C1>();
  report_tc<C2>();
  report_tc<D1>();
  report_tc<D2>();
  
  int a = 0;
  auto f1 = [](int x) { return x*2; };
  auto f2 = [a](int x) { return a*2; };
  auto f3 = [&,a](int x) { return a*2; };
  auto f4 = [](auto x) { std::cout << "called f4 with type: " << type_name(x) << '\n'; return x;};
  
  report_tc(f1);
  report_tc(f2);
  report_tc(f3);
  report_tc(f4);
  (void)f4(3);
  (void)f4(3.5);
}
