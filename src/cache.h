#ifndef CACHE_H
#define CACHE_H

#include <memory>

#include "address.h"
#include "main-memory.h"
#include "mesi-state-automon.h"

#define CacheSize 512

class Cache {
public:
  typedef uint32_t Area;
  typedef std::pair<Area, MesiState_t> CacheLine;

  Cache (std::shared_ptr<MainMemory> mem);

  Cache (void)
    : m_mem (nullptr) {}

  void WriteLocal (Address &addr);
  void ReadLocal (Address &addr);
  void WriteRemote (Address &addr);
  void ReadRemote (Address &addr);

  MesiState_t GetState (uint32_t map, uint32_t* area);
private:
  bool CheckAddress (Address addr);
  void Load2Cache (Address addr);
  // Ptr to Main_mem
  std::shared_ptr<MainMemory> m_mem;
  CacheLine cache[CacheSize];
};


#endif