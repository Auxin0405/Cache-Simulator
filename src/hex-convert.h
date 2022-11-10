#ifndef HEX_CONVERT_H
#define HEX_CONVERT_H

#include <string>
#include <sstream>

// just a method class that all the function are static,
// so that we do not need to to construct it before use it.

class HexConvert {
public:
  static std::string Hex2String (uint32_t hex);
  static uint32_t String2Hex (std::string& str);

private:
  HexConvert () = delete;
};

#endif