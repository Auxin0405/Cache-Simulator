#ifndef ADDRESS_H
#define ADDRESS_H

#include <algorithm>
#include <memory>

// Method Class, to help split address into
// Area address, Cache-map address and Cacheline address.
// As we use 32-bit address, Cache line is 64B, Cache Size
// 32KB, so that the Cacheline address refers to be bit 5-0
// Cache-map address refers to be bit 14-6, and rest to be
// area code.
class Address {
public:
  Address (uint32_t area, uint32_t map) {address = ((area << 15) | (map << 6));}
  Address (uint32_t addr)
    : address (addr) {}
  Address (void)
    : address (0) {};

  // \return Return the Highest 17 bit.
  uint32_t GetArea (void) const {return (address >> 15);}

  // \return Rerturn the bit 14-6
  uint32_t GetMap (void) const {return (address >> 6) & (~((~0) << 9));}

  // Use in Hash Map.
  bool operator == (const Address& addr) const {
    return address == addr.address;
  }

  uint32_t GetAddr (void) const {return address;}

private:
  uint32_t address;
};

// Just use uint32_t hash will be great.
class AddrHash {
public:
  std::size_t operator () (const Address& addr) const {return std::hash<uint32_t> ()(addr.GetAddr ());}
};

#endif