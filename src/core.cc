#include "core.h"
#include "address.h"
#include "hex-convert.h"

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
      cacheVec[i].ReadRemote (addr);
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
Core::PrintState (std::ostream& out, int opt, Address addr)
{
  // static use to log step num global.
  static uint32_t globalStep = 0;
  out << "\t" << globalStep++;

  // LOG the Step Info
  uint32_t area = addr.GetArea ();
  uint32_t map = addr.GetMap ();
  uint32_t a = 0;
  MesiState_t state = mem->GetState (addr);
  out << "\t\t\t\t\t" << HexConvert::Hex2String (addr.GetAddr ());
  out << " \t\t\t\t\t" << MesiStateAutomon::Mesi2String(state) << "\t\t\t\t\t\t\t\t\t";
  for (uint32_t i = 0; i < coreNum; i++) {
    state = cacheVec[i].GetState(map, &a);
    if (a == area)
      out <<  MesiStateAutomon::Mesi2String(state);
    else
      out << "N";
    out << "\t\t\t\t\t\t\t\t\t\t";
  }
  out << std::endl;
}