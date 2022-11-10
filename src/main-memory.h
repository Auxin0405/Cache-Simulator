#ifndef MAIN_MEMORY_H
#define MAIN_MEMORY_H

#include <unordered_map>

#include "mesi-state-automon.h"
#include "address.h"

// Cache will hold the ptr to this main memory
// and all the func is for Cache to call
class MainMemory {
public:
  MainMemory (void);
  void Read (Address addr);
  void Write (Address addr);
  void Invalid (Address addr);

  void WriteBack (Address addr);

  MesiState_t GetState (Address addr);
private:
  std::unordered_map<Address, MesiState_t, AddrHash> m_map;
};


#endif