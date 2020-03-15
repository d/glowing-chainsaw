#include "benchmark/benchmark.h"

inline int lzcnt_slow(uint64_t word) {
  if (word == 0)
    return 8 * sizeof(word);
  return __builtin_clzll(word);
}

__attribute__((target("lzcnt"))) inline int lzcnt_fast(uint64_t word) {
  return __builtin_clzll(word);
}

static void BM_inlined_slow(benchmark::State& state) {
  volatile auto word = state.range(0);
  for (auto _ : state) {
    benchmark::DoNotOptimize(lzcnt_slow(word));
  }
}

static void BM_fast(benchmark::State& state) {
  volatile auto word = state.range(0);
  for (auto _ : state) {
    benchmark::DoNotOptimize(lzcnt_fast(word));
  }
}

__attribute__((target("lzcnt"))) static void BM_inlined_fast(
    benchmark::State& state) {
  volatile auto word = state.range(0);
  for (auto _ : state) {
    benchmark::DoNotOptimize(lzcnt_fast(word));
  }
}

BENCHMARK(BM_inlined_slow)->Arg(0)->Range(1, 64);
BENCHMARK(BM_fast)->Arg(0)->Range(1, 64);
BENCHMARK(BM_inlined_fast)->Arg(0)->Range(1, 64);

BENCHMARK_MAIN();
