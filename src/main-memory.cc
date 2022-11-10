#include "main-memory.h"

MainMemory::MainMemory ()
{
  m_map.clear ();
}

// For Main Memory It may be like only two status to be: Shared and Invalid

// It should be First read.
// else it will come to Other core Cache to read it.
void
MainMemory::Read (Address addr)
{
  if (m_map.find (addr) == m_map.end())
    m_map[addr] = S;
}

// Just write Back
void
MainMemory::WriteBack (Address addr)
{
  // It should be Shared.
  m_map[addr] = S;
}

// For Exclusive change to Modified.
void
MainMemory::Invalid (Address addr)
{
  m_map[addr] = I;
}

void
MainMemory::Write (Address addr)
{
  m_map[addr] = S;
}