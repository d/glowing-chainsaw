#include <x86intrin.h>

#include "lzcnt.h"

static bool go = lzcnt_available();

extern "C" {
__attribute__((target("no-lzcnt"))) int lzcnt_slow(uint64_t word) {
  if (word == 0)
    return 8 * sizeof(word);
  return __builtin_clzll(word);
}
__attribute__((target("lzcnt"))) int lzcnt_fast(uint64_t word) {
  return _lzcnt_u64(word);
}

int lzcnt_static_var(uint64_t word) {
  if (go)
    return lzcnt_fast(word);
  else
    return lzcnt_slow(word);
}
}
