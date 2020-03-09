#include "benchmark/benchmark.h"

#include "lzcnt.h"

static void BM_pfunc(benchmark::State& state) {
  auto word = state.range(0);
  for (auto _ : state) {
    lzcnt_pfunc(word);
  }
}

static void BM_inlined_slow(benchmark::State& state) {
  for (auto _ : state) {
    auto word = state.range(0);
    benchmark::DoNotOptimize(lzcnt_slow(word));
  }
}

static void BM_fast(benchmark::State& state) {
  auto word = state.range(0);
  for (auto _ : state) {
    benchmark::DoNotOptimize(lzcnt_fast(word));
  }
}

__attribute__((target("lzcnt"))) static void BM_inlined_fast(
    benchmark::State& state) {
  for (auto _ : state) {
    auto word = state.range(0);
    benchmark::DoNotOptimize(lzcnt_fast(word));
  }
}

BENCHMARK(BM_pfunc)->Arg(0)->Range(1, 64);
BENCHMARK(BM_inlined_slow)->Arg(0)->Range(1, 64);
BENCHMARK(BM_fast)->Arg(0)->Range(1, 64);
BENCHMARK(BM_inlined_fast)->Arg(0)->Range(1, 64);

BENCHMARK_MAIN();
