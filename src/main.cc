#include <cpuid.h>

#include "benchmark/benchmark.h"

static inline bool lzcnt_available() {
  uint32_t exx[4] = {0, 0, 0, 0};

  __get_cpuid(0x80000001, exx + 0, exx + 1, exx + 2, exx + 3);

  return (exx[2] & bit_ABM) != 0;
}

extern int (*lzcnt_pfunc)(uint64_t word);

__attribute__((target("no-lzcnt"))) inline int lzcnt_slow(uint64_t word) {
  if (word == 0)
    return 8 * sizeof(word);
  return __builtin_clzll(word);
}

__attribute__((target("lzcnt"))) inline int lzcnt_fast(uint64_t word) {
  return __builtin_clzll(word);
}


static bool go = lzcnt_available();

static int lzcnt_choose(uint64_t word) {
  if (lzcnt_available())
    lzcnt_pfunc = lzcnt_fast;
  else
    lzcnt_pfunc = lzcnt_slow;
  return lzcnt_pfunc(word);
}

int (*lzcnt_pfunc)(uint64_t word) = lzcnt_choose;
static void BM_pfunc(benchmark::State& state) {
  auto word = state.range(0);
  for (auto _ : state) {
    lzcnt_pfunc(word);
  }
}

static void BM_inlined_slow(benchmark::State& state) {
  volatile auto word = state.range(0);
  for (auto _ : state) {
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
  volatile auto word = state.range(0);
  for (auto _ : state) {
    benchmark::DoNotOptimize(lzcnt_fast(word));
  }
}

BENCHMARK(BM_pfunc)->Arg(0)->Range(1, 64);
BENCHMARK(BM_inlined_slow)->Arg(0)->Range(1, 64);
BENCHMARK(BM_fast)->Arg(0)->Range(1, 64);
BENCHMARK(BM_inlined_fast)->Arg(0)->Range(1, 64);

BENCHMARK_MAIN();
