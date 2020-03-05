#ifndef LZCNT_H
#define LZCNT_H

#include <cpuid.h>
#include <cstdint>

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

int lzcnt_fast(uint64_t word);

#endif
