#include <cstdio>
#include <range/v3/all.hpp>
#include <string_view>

#ifdef USE_RNG
namespace views = ranges::views;

static constexpr auto intersperse = [](auto delim) {
  auto make_pair = [=](auto val) {
    return views::concat(views::single(delim), views::single(val));
  };
  return views::transform(make_pair) | views::join | views::drop(1);
};

template <typename Func>
static inline void
func(std::string_view str, Func f)
{
  for (char c : (str) | intersperse('\n')) {
    f(c);
  }
}

int
main(int, char** argv)
{
  func("Hello", [](char c) { putchar(c); });
}

#else

inline void 
func(char const* str, char delim)
{
  while (*str) {
    putchar(*str);
    putchar(delim);
    ++str;
  }
}

int
main(int, char**)
{
  auto ptr = "Hello";
  func(ptr, '\n');
}
#endif
