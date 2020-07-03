#include <benchmark/benchmark.h>

#include "functions.h"

void f(benchmark::State& state) {
  for (auto _ : state) {
    f();
  }
}

BENCHMARK(f);
