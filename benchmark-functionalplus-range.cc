#include <string>
#include <iostream>
#include <vector>

#include "benchmark/benchmark.h"
#include "fplus/fplus.hpp"
#include "range/v3/all.hpp"


auto times_3 = [](int i){return 3 * i;};
auto is_odd_int = [](int i){return i % 2 == 0;};
auto as_string_length = [](int i){return std::to_string(i).size();};

auto use_fplus = [](benchmark::State& st, int count) {
  using namespace fplus;
  for (auto _ : st) {
    auto const result = fwd::apply(
      numbers(0, count)
      , fwd::transform(times_3)
      , fwd::drop_if(is_odd_int)
      , fwd::transform(as_string_length)
      , fwd::sum());
    benchmark::DoNotOptimize(result);
  }
};

auto use_range = [](benchmark::State& st, int count) {
  using namespace ranges;

  for (auto _ : st) {
    auto const result =
        accumulate(
            views::ints(0, unreachable)
            | views::take(count)
            | views::transform(times_3)
            | views::remove_if(is_odd_int)
            | views::transform(as_string_length)
            , 0);
    benchmark::DoNotOptimize(result);
  }
};

auto use_forloop = [](benchmark::State& st, int count) {
  for (auto _ : st) {
    int result = 0;
    for (int i = 0; i != count; ++i) {
      auto const x = i * 3;
      if (x % 2 != 0) {
        result += std::to_string(x).size();
      }

    }
    benchmark::DoNotOptimize(result);
  }
};

int main(int argc, char** argv) {
  
  std::vector<int> sizes{1, 10, 100, 1000, 10000, 100000, 1000000, 10000000};
  for (auto size : sizes) {
    std::string forloop_name = "forloop_" + std::to_string(size);
    std::string fplus_name = "fplus_" + std::to_string(size);
    std::string range_name = "range_" + std::to_string(size);
    
    benchmark::RegisterBenchmark(forloop_name.c_str(), use_forloop, size);
    benchmark::RegisterBenchmark(fplus_name.c_str(), use_fplus, size);
    benchmark::RegisterBenchmark(range_name.c_str(), use_range, size);
  }


  benchmark::Initialize(&argc, argv);
  benchmark::RunSpecifiedBenchmarks();
}
