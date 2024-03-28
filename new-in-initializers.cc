#include <iostream>
#include <ostream>
#include <string>


struct S {
  S(char const* str) : s(str) {}
  std::string s;
};

class C {
  private:
    S* ps = new S("cow");
  public:

    ~C() { delete ps; }

    friend std::ostream& operator<<(std::ostream& os, C const& c) {
      os << c.ps->s;
      return os;
    }
};

int main() {
  C c;
  std::cout << c << '\n';
}

