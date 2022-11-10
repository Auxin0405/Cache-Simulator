#include "core.h"

#include <iostream>

Core::Core (uint32_t core_num)
{
  mem = std::make_shared<MainMemory>();
  coreNum = core_num;
  for (uint32_t i = 0; i < core_num; i++) {
    cacheVec.push_back(Cache(mem));
  }
}

void
Core::Write (Address addr, uint32_t index)
{
  cacheVec[index].WriteLocal (addr);
  for (uint32_t i = 0; i < coreNum; i++) {
    if (i != index)
      cacheVec[i].WriteRemote(addr);
  }
}

void
Core::Read (Address addr, uint32_t index)
{
  cacheVec[index].ReadLocal (addr);
  for (uint32_t i = 0; i < coreNum; i++) {
    if (i != index)
      cacheVec[i].ReadRemote(addr);
  }
}

void
Core::Run (uint32_t core, int opt, Address addr)
{
  if (core >= coreNum) {
    std::cout << "input error\n";
    return;
  }
  if (opt == 0)
    Read(addr, core);
  else if (opt == 1)
    Write (addr, core);
}

void
Core::PrintState (std::ostream out, Address addr)
{
  // static use to log step num global.
  static uint32_t globalStep = 0;
  // LOG the Info
}