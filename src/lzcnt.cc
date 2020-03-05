#include "lzcnt.h"

static bool go = lzcnt_available();

__attribute__((target("lzcnt"))) inline int lzcnt_fast(uint64_t word) {
  return __builtin_clzll(word);
}

static int lzcnt_choose(uint64_t word) {
  if (lzcnt_available())
    lzcnt_pfunc = lzcnt_fast;
  else
    lzcnt_pfunc = lzcnt_slow;
  return lzcnt_pfunc(word);
}

int (*lzcnt_pfunc)(uint64_t word) = lzcnt_choose;
