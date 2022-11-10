#ifndef SIMULATOR_H
#define SIMULATOR_H

#include <vector>
#include <fstream>
#include <memory>

#include "cache.h"
#include "main-memory.h"

class Core {
public:
  Core (uint32_t core_num);

  void Write (Address addr, uint32_t index);
  void Read (Address addr, uint32_t index);

  void Run (uint32_t core, int opt, Address addr);

  void PrintState (std::ostream out, Address addr);
private:
  std::shared_ptr<MainMemory> mem;
  std::vector<Cache> cacheVec;
  uint32_t coreNum;
};

#endif