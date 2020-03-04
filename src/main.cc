#include "benchmark/benchmark.h"

#include "lzcnt.h"

static void BM_pfunc(benchmark::State& state) {
  for (auto _ : state) {
    lzcnt_pfunc(8);
  }
}

static void BM_slow(benchmark::State& state) {
  auto word = state.range(0);
  for (auto _ : state) {
    lzcnt_slow(word);
  }
}

static void BM_static_var(benchmark::State& state) {
  for (auto _ : state) {
    lzcnt_static_var(8);
  }
}

static void BM_fast(benchmark::State& state) {
  auto word = state.range(0);
  for (auto _ : state) {
    lzcnt_fast(word);
  }
}

BENCHMARK(BM_pfunc);
BENCHMARK(BM_static_var);
BENCHMARK(BM_slow)->Arg(0)->Range(1, 64);
BENCHMARK(BM_fast)->Arg(0)->Range(1, 64);

BENCHMARK_MAIN();
