// The comparisons done in this work may be dominated by the fact that the
// creation of the range of numbers over which we iterate has to be generated
// by the range-type algorithms; the range is never realized by the for loop
// implementation.

#include <iostream>
#include <string>
#include <vector>

#include "flux.hpp"
#include "fplus/fplus.hpp"
#include "range/v3/all.hpp"

#include "nanobench.h"

auto times_3 = [](int i) { return 3 * i; };
auto is_odd_int = [](int i) { return i % 2 != 0; };
auto as_string_length = [](int i) { return std::to_string(i).size(); };

template <typename FCN>
void
run_bench(FCN&& func, ankerl::nanobench::Bench* bench, std::string const& name)
{
  bench->run(name, (func));
}

int
main()
{
  std::vector<int> sizes;
  int sz = 1;
  while (sz < 10 * 1000 * 1000) {
    sizes.push_back(sz);
    sz *= 4;
  }
  ankerl::nanobench::Bench b;
  b.title("benchmark-functionalplus-range");
  int const PRODUCT = 100 * 1000;
  auto* pb = &b;

  for (auto size : sizes) {
    int const nrep = PRODUCT / size;

    auto use_fplus = [size, nrep, pb]() {
      using namespace fplus;
      pb->minEpochIterations(nrep);
      auto const result = fwd::apply(numbers(0, size),
                                     fwd::transform(times_3),
                                     fwd::drop_if(is_odd_int),
                                     fwd::transform(as_string_length),
                                     fwd::sum());
      ankerl::nanobench::doNotOptimizeAway(result);
    };

    auto use_range = [size, nrep, pb]() {
      using namespace ranges;
      pb->minEpochIterations(nrep);
      auto const result =
        accumulate(views::ints(0, unreachable) | views::take(size) |
                     views::transform(times_3) | views::remove_if(is_odd_int) |
                     views::transform(as_string_length),
                   0);
      ankerl::nanobench::doNotOptimizeAway(result);
    };

    auto use_forloop = [size, nrep, pb]() {
      pb->minEpochIterations(nrep * 100);
      std::size_t result = 0;
      for (int i = 0; i != size; ++i) {
        auto const x = i * 3;
        if (x % 2 != 0) {
          result += std::to_string(x).size();
        }
      }
      ankerl::nanobench::doNotOptimizeAway(result);
    };

    auto use_flux = [size, nrep, pb]() {
      pb->minEpochIterations(nrep);
      std::size_t const result =
        flux::ints()
          .take(size)
          .map([](int i) { return 3 * i; })
          .filter(flux::pred::even)
          .map([](int i) { return std::to_string(i).size(); })
          .sum();
      ankerl::nanobench::doNotOptimizeAway(result);
    };

    std::string forloop_name = "forloop_" + std::to_string(size);
    std::string fplus_name = "fplus_" + std::to_string(size);
    std::string range_name = "range_" + std::to_string(size);
    std::string flux_name = "flux_" + std::to_string(size);

    run_bench(use_forloop, &b, forloop_name.c_str());
    run_bench(use_fplus, &b, fplus_name.c_str());
    run_bench(use_range, &b, range_name.c_str());
    run_bench(std::move(use_flux), &b, flux_name.c_str());
  }
}
