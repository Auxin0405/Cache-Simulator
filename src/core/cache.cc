#include "cache.h"

Cache::Cache(std::shared_ptr<MainMemory> mem)
  :m_mem (mem)
{
  for (uint32_t i = 0; i < CacheSize; i++) {
    cache[i].first = 0;
    cache[i].second = I;
  }
}

bool
Cache::CheckAddress (Address addr)
{
  uint32_t area = addr.GetArea ();
  uint32_t map = addr.GetMap ();
  if (cache[map].first == area && cache[map].second != I)
    return true;
  return false;
}

void
Cache::Load2Cache (Address addr)
{
  uint32_t area = addr.GetArea ();
  uint32_t map = addr.GetMap ();

  // Cache Miss and Modified, need Write Back First.
  if (cache[map].first != area && cache[map].second == M) {
      // The Modified and should be write back First.
      m_mem->WriteBack (Address (area, map));
  }
  cache[map].first = area;
  cache[map].second = S;
}

void
Cache::WriteLocal (Address &addr)
{
  // If not hit, load it to cache
  if (!CheckAddress(addr))
    Load2Cache (addr);

  uint32_t map = addr.GetMap ();
  MesiState_t cur = cache[map].second;
  cache[map].second = MesiStateAutomon::TransferState(cur, MesiStateAutomon::WL);

  //  Comes from E to M, we need to Invalid mem.
  if (cache[map].second == M)
    m_mem->Invalid (addr);
}

void
Cache::ReadLocal (Address &addr)
{
  // If not hit, load it to cache
  if (!CheckAddress(addr))
    Load2Cache (addr);
}

void
Cache::WriteRemote (Address &addr)
{
  // Write Hit.
  if (CheckAddress (addr)) {
    uint32_t map = addr.GetMap ();
    MesiState_t cur = cache[map].second;
    cache[map].second = MesiStateAutomon::TransferState(cur, MesiStateAutomon::WR);
  }
}

void
Cache::ReadRemote (Address &addr)
{
  if (CheckAddress(addr)) {
    uint32_t map = addr.GetMap ();
    MesiState_t cur = cache[map].second;
    cache[map].second = MesiStateAutomon::TransferState(cur, MesiStateAutomon::RR);
  }
}

MesiState_t
Cache::GetState (uint32_t map, uint32_t* area)
{
  uint32_t a = cache[map].first;
  *area = a;
  return cache[map].second;
}