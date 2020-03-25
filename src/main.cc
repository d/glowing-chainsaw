#include "benchmark/benchmark.h"

inline int lzcnt(uint64_t word) {
  if (word == 0)
    return 8 * sizeof(word);
  return __builtin_clzll(word);
}

// word != 0
inline int bsr(uint64_t word) {
  return 8 * sizeof(word) - 1 - __builtin_clzll(word);
}

// word != 0
inline int ceil_log2(uint64_t word) {
  return 8 * sizeof(word) - lzcnt(word - 1);
}

inline int64_t next_power_of_two_DR(int64_t word) {
  if (0 == (word & (word - 1)))
    return word;
  return (int64_t)1 << (bsr(word) + 1);
}

inline int64_t next_power_of_two(int64_t word) {
  return (int64_t)1 << ceil_log2(word);
}

static void BM_next_power_of_two(benchmark::State& state) {
  volatile auto word = state.range(0);
  for (auto _ : state) {
    benchmark::DoNotOptimize(next_power_of_two(word));
  }
}

static void BM_next_power_of_two_DR(benchmark::State& state) {
  volatile auto word = state.range(0);
  for (auto _ : state) {
    benchmark::DoNotOptimize(next_power_of_two_DR(word));
  }
}

BENCHMARK(BM_next_power_of_two)->Range(1, 0x200)->DenseRange(0x401, 0x440, 17);
BENCHMARK(BM_next_power_of_two_DR)->Range(1, 0x200)->DenseRange(0x401, 0x440, 17);

BENCHMARK_MAIN();
